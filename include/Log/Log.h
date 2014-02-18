/*******************************************************************************
 *  @file      Log.h 2013\12\12 15:19:07 $
 *  @author    Wang Xiaotao<wangxiaotao1980@gmail.com> (中文编码测试)
 *
 ******************************************************************************/

#ifndef LOG_0E3AE1A3_AE3C_4857_8BC5_F9F2CD79276C_H__
#define LOG_0E3AE1A3_AE3C_4857_8BC5_F9F2CD79276C_H__

#include "LogConfig.h"
#include "LogError.h"
#include "LogUtils.h"

#include <time.h>
#include <iostream>
/******************************************************************************/


#define LOG_TIME_OUTPUT()  \
    { \
        time_t temptm = ::time(0);              \
        tm* ptheTime = ::localtime(&temptm);    \
        std::clog << std::right << std::setw(4) << std::setfill('0') << ptheTime->tm_year + 1900  << "/"  \
                  << std::right << std::setw(2) << std::setfill('0') << ptheTime->tm_mon + 1      << "/"  \
                  << std::right << std::setw(2) << std::setfill('0') << ptheTime->tm_mday         << " "  \
                  << std::right << std::setw(2) << std::setfill('0') << ptheTime->tm_hour         <<":"   \
                  << std::right << std::setw(2) << std::setfill('0') << ptheTime->tm_min          <<":"   \
                  << std::right << std::setw(2) << std::setfill('0') << ptheTime->tm_sec          <<" ";  \
    }

#define WRITE_LOG_WITH_LOCK_1(a)     \
    {                                \
    CPS_LOG_NAMESPACE::LogLock();    \
    LOG_TIME_OUTPUT()                \
    std::clog << a << std::endl;     \
    CPS_LOG_NAMESPACE::LogUnLock();    \
    }

#define WRITE_LOG_WITH_LOCK_2(a, b)  \
    {          \
    CPS_LOG_NAMESPACE::LogLock();        \
    LOG_TIME_OUTPUT()                \
    std::clog << a << std::endl;  \
    std::clog << "                    " << b << std::endl; \
    CPS_LOG_NAMESPACE::LogUnLock(); \
    }



#define WRITE_LOG_WITH_LOCK_3(a, b, c)  \
    {          \
    CPS_LOG_NAMESPACE::LogLock();        \
        LOG_TIME_OUTPUT()                \
        std::clog << a << std::endl;  \
        std::clog << "                    " << b << std::endl; \
        std::clog << "                    " << c << std::endl; \
    CPS_LOG_NAMESPACE::LogUnLock(); \
    }


#define WRITE_LOG_WITH_LOCK_4(a, b, c, d)  \
    {          \
    CPS_LOG_NAMESPACE::LogLock();        \
    LOG_TIME_OUTPUT()                \
    std::clog << a << std::endl;  \
    std::clog << "                    " << b << std::endl; \
    std::clog << "                    " << c << std::endl; \
    std::clog << "                    " << d << std::endl; \
    CPS_LOG_NAMESPACE::LogUnLock(); \
    }

/******************************************************************************/
#endif// LOG_0E3AE1A3_AE3C_4857_8BC5_F9F2CD79276C_H__