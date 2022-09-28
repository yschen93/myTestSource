//
// Created by 谭鑫 on 2022/9/28.
//
#include <iostream>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/thread.hpp>
#include <boost/bind/bind.hpp>
#include <sstream>

std::string now_str()
{
    // Get current time from the clock, using microseconds resolution
    const boost::posix_time::ptime now =
            boost::posix_time::microsec_clock::local_time();

    // Get the time offset in current day
    const boost::posix_time::time_duration td = now.time_of_day();

    //
    // Extract hours, minutes, seconds and milliseconds.
    //
    // Since there is no direct accessor ".milliseconds()",
    // milliseconds are computed _by difference_ between total milliseconds
    // (for which there is an accessor), and the hours/minutes/seconds
    // values previously fetched.
    //
    const long hours        = td.hours();
    const long minutes      = td.minutes();
    const long seconds      = td.seconds();
    const long milliseconds = td.total_milliseconds() -
                              ((hours * 3600 + minutes * 60 + seconds) * 1000);
    char buf[40];
    sprintf(buf, "%02ld:%02ld:%02ld.%03ld",
            hours, minutes, seconds, milliseconds);

    return buf;
}

using namespace boost::asio;

class impl
{
public:
    impl()
    :strand_(boost::asio::make_strand(io_))
    ,timer1_(io_)
    ,timer2_(io_)
    ,count_(0)
    {

    }
    void Init()
    {
        std::cout << "start timer, now: " << now_str() << std::endl;
        timer1_.expires_from_now(std::chrono::seconds(1));
        timer2_.expires_from_now(std::chrono::seconds(1));
        timer1_.async_wait(boost::asio::bind_executor(
                strand_, boost::bind(&impl::TimerHandler, this, std::placeholders::_1, 1)));
        timer2_.async_wait(boost::asio::bind_executor(
                strand_, boost::bind(&impl::TimerHandler, this, std::placeholders::_1, 2)));

        work_ = new boost::asio::io_context::work(io_);
        thread_ = boost::thread(
            [this](){
                io_.run();
            });
    }
    void TimerHandler(boost::system::error_code const& ec, size_t thread_idx)
    {
        if (count_ < 5)
        {
            std::stringstream ss;
            ss << "[" << thread_idx << "]: " << "count: " << count_;
            ss << ", now: " << now_str();
            std::cout << ss.str() << std::endl;
            ++count_;
            if (1 == thread_idx)
            {
                timer1_.expires_at(timer1_.expiry() + std::chrono::seconds(1));
                timer1_.async_wait(boost::asio::bind_executor(
                    strand_, boost::bind(&impl::TimerHandler, this, std::placeholders::_1, 1)));
            }
            else
            {
                timer2_.expires_at(timer2_.expiry() + std::chrono::seconds(1));
                timer2_.async_wait(boost::asio::bind_executor(
                    strand_, boost::bind(&impl::TimerHandler, this, std::placeholders::_1, 2)));
            }
        }
    }
    void Stop()
    {
        delete work_;
        boost::system::error_code ec;
        timer1_.cancel(ec);
        timer2_.cancel(ec);
        if (!io_.stopped())
            io_.stop();
        if (thread_.joinable())
            thread_.join();
    }
private:
    boost::asio::io_context io_;
    boost::asio::strand<boost::asio::io_context::executor_type> strand_;
    boost::asio::steady_timer timer1_;
    boost::asio::steady_timer timer2_;
    boost::thread thread_;
    boost::asio::io_context::work* work_;
    size_t count_;


};
int main(int argc, char *argv[])
{
    impl imp;
    imp.Init();
    while (1);
}