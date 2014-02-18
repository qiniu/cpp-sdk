/******************************************************************************* 
 *  @file      IQiniuRemoteBatchFilesTestCase.cpp 2013\11\25 18:35:50 $
 *  @author    Wang Xiaotao<wangxiaotao1980@gmail.com> (中文编码测试)
 ******************************************************************************/

#include "gtest/gtest.h"
#include "Qiniu/Qiniu.h"

#include <iostream>
#include <fstream>



TEST(IQiniuRemoteBatchFilesTest, TestCase0_uploadFile)
{
    std::ofstream myfile (".\\test.file");
    if (myfile.is_open())
    {
        myfile << "This is a line.\n";
        myfile << "This is another line.\n";
        for (int i = 0; i < 1000; ++i)
        {
            myfile << i ;
        }
        myfile.close();
    }
    else
    {
        std::cout << "Unable to open file";
    }

    QINIU_NAMESPACE::QiniuUtils::Initialize();

    QINIU_NAMESPACE::QiniuToken token;

    token.m_access_key = "og9UTrj8I83ndelDQrzlpjXS8HwtiQVMV2S_v7D1";
    token.m_secret_key = "oGUsG0nvsCcltrlkci08qY48DaM-uC7MQjsWRPe0";

    QINIU_NAMESPACE::QiniuPutPolicy  putPolicy;
    QINIU_NAMESPACE::QiniuIoPutExtra ioPutExtra;


    QINIU_NAMESPACE::IQiniuUploadFile* qiniuInterface = QINIU_NAMESPACE::QiniuFactory::CreateIQiniuUploadFileObj();


    putPolicy.m_bucketName = "testqiniucppsdk";
    putPolicy.m_keyName    = "1.txt";  //2 | 614

    const char* plocalFile = ".\\test.file";
    std::string resultStr;
    QINIU_NAMESPACE::QiniuCode code = qiniuInterface->uploadFile(token, putPolicy, ioPutExtra, true, plocalFile, NULL, resultStr);

    GTEST_ASSERT_EQ(code, 0) << "The code is : " << (code >> 16) << " | " << (code << 16 >> 16) 
        << "\nthe result is" << qiniuInterface->getLastErrorInfo();

    putPolicy.m_keyName    = "2.txt"; 
    code = qiniuInterface->uploadFile(token, putPolicy, ioPutExtra, true, plocalFile, NULL, resultStr);
    GTEST_ASSERT_EQ(code, 0) << "The code is : " << (code >> 16) << " | " << (code << 16 >> 16) 
        << "\nthe result is" << qiniuInterface->getLastErrorInfo();

    putPolicy.m_keyName    = "3.txt"; 
    code = qiniuInterface->uploadFile(token, putPolicy, ioPutExtra, true, plocalFile, NULL, resultStr);
    GTEST_ASSERT_EQ(code, 0) << "The code is : " << (code >> 16) << " | " << (code << 16 >> 16) 
        << "\nthe result is" << qiniuInterface->getLastErrorInfo();

    putPolicy.m_keyName    = "4.txt"; 
    code = qiniuInterface->uploadFile(token, putPolicy, ioPutExtra, true, plocalFile, NULL, resultStr);
    GTEST_ASSERT_EQ(code, 0) << "The code is : " << (code >> 16) << " | " << (code << 16 >> 16) 
        << "\nthe result is" << qiniuInterface->getLastErrorInfo();

    putPolicy.m_keyName    = "5.txt"; 
    code = qiniuInterface->uploadFile(token, putPolicy, ioPutExtra, true, plocalFile, NULL, resultStr);
    GTEST_ASSERT_EQ(code, 0) << "The code is : " << (code >> 16) << " | " << (code << 16 >> 16) 
        << "\nthe result is" << qiniuInterface->getLastErrorInfo();


    QINIU_NAMESPACE::QiniuFactory::DestoryIQiniuUploadFileObj(qiniuInterface);
    QINIU_NAMESPACE::QiniuUtils::Terminate();
}



TEST(IQiniuRemoteBatchFilesTest, getRemoteBatchFilesInfoTestCase)
{
    QINIU_NAMESPACE::QiniuUtils::Initialize();

    QINIU_NAMESPACE::QiniuToken token;

    token.m_access_key = "og9UTrj8I83ndelDQrzlpjXS8HwtiQVMV2S_v7D1";
    token.m_secret_key = "oGUsG0nvsCcltrlkci08qY48DaM-uC7MQjsWRPe0";


    QINIU_NAMESPACE::IQiniuRemoteBatchFiles* qiniuInterface 
        = QINIU_NAMESPACE::QiniuFactory::CreateIQiniuRemoteBatchFilesObj();

    // HTTP 代理测试，通过
    //QINIU_NAMESPACE::ProxyInfo proxyInfo;

    //proxyInfo.m_ip = "192.168.1.122";
    //proxyInfo.m_port = 8123;
    //proxyInfo.m_proxyMode = QINIU_NAMESPACE::ProxyHTTP;
    //proxyInfo.m_isUsingPwd = true;
    //proxyInfo.m_passwd = "123";
    //proxyInfo.m_user = "test";

    //qiniuInterface->setProxyInfo(proxyInfo);
    //

     

    std::string resultStr;

    const char* bucketName = "testqiniucppsdk";

    QINIU_NAMESPACE::QiniuBucketKey bucketKey[] = {
                                                    {bucketName, "1.txt"},
                                                    {bucketName, "2.txt"},
                                                    {bucketName, "3.txt"},
                                                    {bucketName, "4.txt"},
                                                    {bucketName, "5.txt"},
                                                  };

    QINIU_NAMESPACE::QiniuCode code 
        = qiniuInterface->getRemoteBatchFilesInfo( token, 
                                                   bucketKey, 
                                                   sizeof(bucketKey)/ sizeof(QINIU_NAMESPACE::QiniuBucketKey), 
                                                   resultStr);

    GTEST_ASSERT_EQ(code, 0) << "The code is : " << (code >> 16) << " | " << (code << 16 >> 16) 
        << "\nthe result is" << qiniuInterface->getLastErrorInfo();


    QINIU_NAMESPACE::QiniuFactory::DestoryIQiniuRemoteBatchFilesObj(qiniuInterface);

    QINIU_NAMESPACE::QiniuUtils::Terminate();
}

TEST(IQiniuRemoteBatchFilesTest, moveRemoteBatchFilesTestCase)
{
    QINIU_NAMESPACE::QiniuUtils::Initialize();

    QINIU_NAMESPACE::QiniuToken token;

    token.m_access_key = "og9UTrj8I83ndelDQrzlpjXS8HwtiQVMV2S_v7D1";
    token.m_secret_key = "oGUsG0nvsCcltrlkci08qY48DaM-uC7MQjsWRPe0";


    QINIU_NAMESPACE::IQiniuRemoteBatchFiles* qiniuInterface 
        = QINIU_NAMESPACE::QiniuFactory::CreateIQiniuRemoteBatchFilesObj();

    std::string resultStr;

    const char* bucketName = "testqiniucppsdk";

    QINIU_NAMESPACE::QiniuSrcAndDestBucketKey bucketKey[] = {
        {bucketName, "1.txt", bucketName, "1_copy.txt"},
        {bucketName, "2.txt", bucketName, "2_copy.txt"},
        {bucketName, "3.txt", bucketName, "3_copy.txt"},
        {bucketName, "4.txt", bucketName, "4_copy.txt"},
        {bucketName, "5.txt", bucketName, "5_copy.txt"},
    };

    QINIU_NAMESPACE::QiniuCode code 
        = qiniuInterface->moveRemoteBatchFiles( token, 
                                                bucketKey, 
                                                sizeof(bucketKey)/ sizeof(QINIU_NAMESPACE::QiniuSrcAndDestBucketKey), 
                                                resultStr);

    GTEST_ASSERT_EQ(code, 0) << "The code is : " << (code >> 16) << " | " << (code << 16 >> 16) 
        << "\nthe result is" << qiniuInterface->getLastErrorInfo();

    QINIU_NAMESPACE::QiniuSrcAndDestBucketKey bucketKeys[] = {
        {bucketName, "1_copy.txt", bucketName, "1.txt"},
        {bucketName, "2_copy.txt", bucketName, "2.txt"},
        {bucketName, "3_copy.txt", bucketName, "3.txt"},
        {bucketName, "4_copy.txt", bucketName, "4.txt"},
        {bucketName, "5_copy.txt", bucketName, "5.txt"},
    };

    code = qiniuInterface->moveRemoteBatchFiles( token, 
        bucketKeys, 
        sizeof(bucketKeys)/ sizeof(QINIU_NAMESPACE::QiniuSrcAndDestBucketKey), 
        resultStr);

    GTEST_ASSERT_EQ(code, 0) << "The code is : " << (code >> 16) << " | " << (code << 16 >> 16) 
        << "\nthe result is" << qiniuInterface->getLastErrorInfo();

    QINIU_NAMESPACE::QiniuFactory::DestoryIQiniuRemoteBatchFilesObj(qiniuInterface);

    QINIU_NAMESPACE::QiniuUtils::Terminate();
}



TEST(IQiniuRemoteBatchFilesTest, copyRemoteBatchFilesTestCase)
{
    QINIU_NAMESPACE::QiniuUtils::Initialize();

    QINIU_NAMESPACE::QiniuToken token;

    token.m_access_key = "og9UTrj8I83ndelDQrzlpjXS8HwtiQVMV2S_v7D1";
    token.m_secret_key = "oGUsG0nvsCcltrlkci08qY48DaM-uC7MQjsWRPe0";


    QINIU_NAMESPACE::IQiniuRemoteBatchFiles* qiniuInterface 
        = QINIU_NAMESPACE::QiniuFactory::CreateIQiniuRemoteBatchFilesObj();

    std::string resultStr;

    const char* bucketName = "testqiniucppsdk";

    QINIU_NAMESPACE::QiniuSrcAndDestBucketKey bucketKey[] = {
        {bucketName, "1.txt", bucketName, "1_copy.txt"},
        {bucketName, "2.txt", bucketName, "2_copy.txt"},
        {bucketName, "3.txt", bucketName, "3_copy.txt"},
        {bucketName, "4.txt", bucketName, "4_copy.txt"},
        {bucketName, "5.txt", bucketName, "5_copy.txt"},
    };

    QINIU_NAMESPACE::QiniuCode code 
        = qiniuInterface->copyRemoteBatchFiles( token, 
        bucketKey, 
        sizeof(bucketKey)/ sizeof(QINIU_NAMESPACE::QiniuSrcAndDestBucketKey), 
        resultStr);

    GTEST_ASSERT_EQ(code, 0) << "The code is : " << (code >> 16) << " | " << (code << 16 >> 16) 
        << "\nthe result is" << qiniuInterface->getLastErrorInfo();

    QINIU_NAMESPACE::QiniuFactory::DestoryIQiniuRemoteBatchFilesObj(qiniuInterface);

    QINIU_NAMESPACE::QiniuUtils::Terminate();
}


TEST(IQiniuRemoteBatchFilesTest, deleteRemoteBatchFilesTestCase)
{
    QINIU_NAMESPACE::QiniuUtils::Initialize();

    QINIU_NAMESPACE::QiniuToken token;

    token.m_access_key = "og9UTrj8I83ndelDQrzlpjXS8HwtiQVMV2S_v7D1";
    token.m_secret_key = "oGUsG0nvsCcltrlkci08qY48DaM-uC7MQjsWRPe0";


    QINIU_NAMESPACE::IQiniuRemoteBatchFiles* qiniuInterface 
        = QINIU_NAMESPACE::QiniuFactory::CreateIQiniuRemoteBatchFilesObj();

    std::string resultStr;

    const char* bucketName = "testqiniucppsdk";

    QINIU_NAMESPACE::QiniuBucketKey bucketKey[] = {
        {bucketName, "1_copy.txt"},
        {bucketName, "2_copy.txt"},
        {bucketName, "3_copy.txt"},
        {bucketName, "4_copy.txt"},
        {bucketName, "5_copy.txt"},
    };

    QINIU_NAMESPACE::QiniuCode code 
        = qiniuInterface->deleteRemoteBatchFiles( token, 
        bucketKey, 
        sizeof(bucketKey)/ sizeof(QINIU_NAMESPACE::QiniuBucketKey), 
        resultStr);

    GTEST_ASSERT_EQ(code, 0) << "The code is : " << (code >> 16) << " | " << (code << 16 >> 16) 
        << "\nthe result is" << qiniuInterface->getLastErrorInfo();

    QINIU_NAMESPACE::QiniuFactory::DestoryIQiniuRemoteBatchFilesObj(qiniuInterface);

    QINIU_NAMESPACE::QiniuUtils::Terminate();
}


// 测试方法 IQiniuRemoteFile::deleteRemoteFile()
// 删除文件
TEST(IQiniuRemoteBatchFilesTest, TestCase0_deleteRemoteFile)
{

    QINIU_NAMESPACE::QiniuUtils::Initialize();

    QINIU_NAMESPACE::QiniuToken token;

    token.m_access_key = "og9UTrj8I83ndelDQrzlpjXS8HwtiQVMV2S_v7D1";
    token.m_secret_key = "oGUsG0nvsCcltrlkci08qY48DaM-uC7MQjsWRPe0";


    QINIU_NAMESPACE::IQiniuRemoteFile* qiniuInterface = QINIU_NAMESPACE::QiniuFactory::CreateIQiniuRemoteFileObj();


    QINIU_NAMESPACE::QiniuCode 
    
    code = qiniuInterface->deleteRemoteFile(token, "testqiniucppsdk", "1.txt");

    GTEST_ASSERT_EQ(code, 0) << "The code is : " << (code >> 16) << " | " << (code << 16 >> 16) 
        << "\nthe result is" << qiniuInterface->getLastErrorInfo();

    code = qiniuInterface->deleteRemoteFile(token, "testqiniucppsdk", "2.txt");

    GTEST_ASSERT_EQ(code, 0) << "The code is : " << (code >> 16) << " | " << (code << 16 >> 16) 
        << "\nthe result is" << qiniuInterface->getLastErrorInfo();


    code = qiniuInterface->deleteRemoteFile(token, "testqiniucppsdk", "3.txt");

    GTEST_ASSERT_EQ(code, 0) << "The code is : " << (code >> 16) << " | " << (code << 16 >> 16) 
        << "\nthe result is" << qiniuInterface->getLastErrorInfo();

    code = qiniuInterface->deleteRemoteFile(token, "testqiniucppsdk", "4.txt");

    GTEST_ASSERT_EQ(code, 0) << "The code is : " << (code >> 16) << " | " << (code << 16 >> 16) 
        << "\nthe result is" << qiniuInterface->getLastErrorInfo();

    code = qiniuInterface->deleteRemoteFile(token, "testqiniucppsdk", "5.txt");

    GTEST_ASSERT_EQ(code, 0) << "The code is : " << (code >> 16) << " | " << (code << 16 >> 16) 
        << "\nthe result is" << qiniuInterface->getLastErrorInfo();


    QINIU_NAMESPACE::QiniuFactory::DestoryIQiniuRemoteFileObj(qiniuInterface);
    QINIU_NAMESPACE::QiniuUtils::Terminate();
}




// 
// -----------------------------------------------------------------------------