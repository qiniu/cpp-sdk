/******************************************************************************* 
 *  @file      HttpAccessUtils.cpp 2013\3\8 11:35:05 $
 *  @author    Wang Xiaotao<wangxiaotao1980@gmail.com> 中文编码测试
 ******************************************************************************/

#include "HttpAccess/HttpAccessUtils.h"

#include <map>
#include <string>

#include "curl/curl.h"
#include "boost/assign.hpp"
/******************************************************************************/

namespace 
{
   const static std::map<UInt32, std::string> s_ErrorCodeMapForCurl
       = boost::assign::list_of
       (std::make_pair( 1, std::string("Unsupported protocol. This build of curl has no support for this protocol.")))
       (std::make_pair( 2, std::string("Failed to initialize.")))
       (std::make_pair( 3, std::string("URL malformed. The syntax was not correct.")))
       (std::make_pair( 4, std::string("A feature or option that was needed to perform the desired request was not enabled or was explicitly disabled at build-time. To make curl able to do this, you probably need another build of libcurl!")))
       (std::make_pair( 5, std::string("Couldn't resolve proxy. The given proxy host could not be resolved.")))

       (std::make_pair( 6, std::string("Couldn't resolve host. The given remote host was not resolved.")))
       (std::make_pair( 7, std::string("Failed to connect to host.")))
       (std::make_pair( 8, std::string("FTP weird server reply. The server sent data curl couldn't parse.")))
       (std::make_pair( 9, std::string("FTP access denied. The server denied login or denied access to the particular resource or directory you wanted  to  reach. Most often you tried to change to a directory that doesn't exist on the server.")))
       (std::make_pair(11, std::string("FTP weird PASS reply. Curl couldn't parse the reply sent to the PASS request.")))

       (std::make_pair(13, std::string("FTP weird PASV reply, Curl couldn't parse the reply sent to the PASV request.")))
       (std::make_pair(14, std::string("FTP weird 227 format. Curl couldn't parse the 227-line the server sent.")))
       (std::make_pair(15, std::string("FTP can't get host. Couldn't resolve the host IP we got in the 227-line.")))
       (std::make_pair(17, std::string("FTP couldn't set binary. Couldn't change transfer method to binary.")))
       (std::make_pair(18, std::string("Partial file. Only a part of the file was transferred.")))

       (std::make_pair(19, std::string("FTP couldn't download/access the given file, the RETR (or similar) command failed.")))
       (std::make_pair(21, std::string("FTP quote error. A quote command returned error from the server.")))
       (std::make_pair(22, std::string("HTTP  page  not retrieved. The requested url was not found or returned another error with the HTTP error code being 400 or above. This return code only appears if -f, --fail is used.")))
       (std::make_pair(23, std::string("Write error. Curl couldn't write data to a local filesystem or similar.")))
       (std::make_pair(25, std::string("FTP couldn't STOR file. The server denied the STOR operation, used for FTP uploading.")))

       (std::make_pair(26, std::string("Read error. Various reading problems.")))
       (std::make_pair(27, std::string("Out of memory. A memory allocation request failed.")))
       (std::make_pair(28, std::string("Operation timeout. The specified time-out period was reached according to the conditions.")))
       (std::make_pair(30, std::string("FTP PORT failed. The PORT command failed. Not all FTP servers support the PORT command, try doing a  transfer  using  PASV instead!")))
       (std::make_pair(31, std::string("FTP couldn't use REST. The REST command failed. This command is used for resumed FTP transfers.")))

       (std::make_pair(33, std::string("HTTP range error. The range \"command\" didn't work.")))
       (std::make_pair(34, std::string("HTTP post error. Internal post-request generation error.")))
       (std::make_pair(35, std::string("SSL connect error. The SSL handshaking failed.")))
       (std::make_pair(36, std::string("FTP bad download resume. Couldn't continue an earlier aborted download.")))
       (std::make_pair(37, std::string("FILE couldn't read file. Failed to open the file. Permissions?")))

       (std::make_pair(38, std::string("LDAP cannot bind. LDAP bind operation failed.")))
       (std::make_pair(39, std::string("LDAP search failed.")))
       (std::make_pair(41, std::string("Function not found. A required LDAP function was not found.")))
       (std::make_pair(42, std::string("Aborted by callback. An application told curl to abort the operation.")))
       (std::make_pair(43, std::string("Internal error. A function was called with a bad parameter.")))

       (std::make_pair(45, std::string("Interface error. A specified outgoing interface could not be used.")))
       (std::make_pair(47, std::string("Too many redirects. When following redirects, curl hit the maximum amount.")))
       (std::make_pair(48, std::string("Unknown  option  specified to libcurl. This indicates that you passed a weird option to curl that was passed on to libcurl and rejected. Read up in the manual!")))
       (std::make_pair(49, std::string("Malformed telnet option.")))
       (std::make_pair(51, std::string("The peer's SSL certificate or SSH MD5 fingerprint was not OK.")))

       (std::make_pair(52, std::string("The server didn't reply anything, which here is considered an error.")))
       (std::make_pair(53, std::string("SSL crypto engine not found.")))
       (std::make_pair(54, std::string("Cannot set SSL crypto engine as default.")))
       (std::make_pair(55, std::string("Failed sending network data.")))
       (std::make_pair(56, std::string("Failure in receiving network data.")))

       (std::make_pair(58, std::string("Problem with the local certificate.")))
       (std::make_pair(59, std::string("Couldn't use specified SSL cipher.")))
       (std::make_pair(60, std::string("Peer certificate cannot be authenticated with known CA certificates.")))
       (std::make_pair(61, std::string("Unrecognized transfer encoding.")))
       (std::make_pair(62, std::string("Invalid LDAP URL.")))

       (std::make_pair(63, std::string("Maximum file size exceeded.")))
       (std::make_pair(64, std::string("Requested FTP SSL level failed.")))
       (std::make_pair(65, std::string("Sending the data requires a rewind that failed.")))
       (std::make_pair(66, std::string("Failed to initialise SSL Engine.")))
       (std::make_pair(67, std::string("The user name, password, or similar was not accepted and curl failed to log in.")))

       (std::make_pair(68, std::string("File not found on TFTP server.")))
       (std::make_pair(69, std::string("Permission problem on TFTP server.")))
       (std::make_pair(70, std::string("Out of disk space on TFTP server.")))
       (std::make_pair(71, std::string("Illegal TFTP operation.")))
       (std::make_pair(72, std::string("Unknown TFTP transfer ID.")))

       (std::make_pair(73, std::string("File already exists (TFTP).")))
       (std::make_pair(74, std::string("No such user (TFTP).")))
       (std::make_pair(75, std::string("Character conversion failed.")))
       (std::make_pair(76, std::string("Character conversion functions required.")))
       (std::make_pair(77, std::string("Problem with reading the SSL CA cert (path? access rights?).")))

       (std::make_pair(78, std::string("The resource referenced in the URL does not exist.")))
       (std::make_pair(79, std::string("An unspecified error occurred during the SSH session.")))
       (std::make_pair(80, std::string("Failed to shut down the SSL connection.")))
       (std::make_pair(82, std::string("Could not load CRL file, missing or wrong format (added in 7.19.0).")))
       (std::make_pair(83, std::string("Issuer check failed (added in 7.19.0).")))

       (std::make_pair(84, std::string("The FTP PRET command failed")))
       (std::make_pair(85, std::string("RTSP: mismatch of CSeq numbers")))
       (std::make_pair(86, std::string("RTSP: mismatch of Session Identifiers")))
       (std::make_pair(87, std::string("unable to parse FTP file list")))
       (std::make_pair(88, std::string("FTP chunk callback reported error")))
       ;

   const static std::map<UInt32, std::string> s_ErrorCodeMapForHttpAccess
       = boost::assign::list_of
       (std::make_pair( 1, std::string("Failed to initialize HttpAccess Model")))
       (std::make_pair( 2, std::string("Failed to initialize Curl")))
       (std::make_pair( 3, std::string("Failed to parse HTTP response code")))
       ;

    const static std::string UnknownErrorInfo("Unknown Error Code.");

    static std::string s_userAgent;
}

CPS_HTTPACCESS_NAMESPACE_BEGIN
// -----------------------------------------------------------------------------
// public   
HttpAccessCode Initialize()
{
    CURLcode resutlCode = ::curl_global_init(CURL_GLOBAL_ALL);
    if (resutlCode == CURLE_OK)
    {
        return HTTPACCESS_OK;             // curl 初始化 成功 
    }
    else
    {
        return HTTPACCESS_MODEL_INIT_FAIL; // curl 初始化 失败
    }
}

// -----------------------------------------------------------------------------
// public   
void Terminate()
{
    ::curl_global_cleanup();
}

// -----------------------------------------------------------------------------
// public   
const char* getErrorCodeInfo( HttpAccessCode code)
{

    HttpAccessCode flagCode = (code & 0xFFFF0000U) >> 16;

    switch (flagCode)
    {
    case 0U:
    {

        std::map<UInt32, std::string>::const_iterator cit = s_ErrorCodeMapForHttpAccess.find(code & 0xFFFFU);
        if (cit != s_ErrorCodeMapForCurl.end())
        {
            return cit->second.c_str();
        }
        else
        {
            return UnknownErrorInfo.c_str();
        }
        break;
    }
    case 1U:
    {
        std::map<UInt32, std::string>::const_iterator cit = s_ErrorCodeMapForCurl.find(code & 0xFFFFU);
        if (cit != s_ErrorCodeMapForCurl.end())
        {
            return cit->second.c_str();
        }
        else
        {
            return UnknownErrorInfo.c_str();
        }
        break;
    }
    default:
        return UnknownErrorInfo.c_str();
        break;
    }
}

CPS_HTTPACCESS_NAMESPACE_END


// 
// -----------------------------------------------------------------------------
