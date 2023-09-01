#include <jni.h>
#include <string>
#include <gmssl/sm2.h>
#include <gmssl/sm4.h>
#include "log.h"
#include "gmssl/error.h"
#include "gmssl/x509_cer.h"
#include "gmssl/sm9.h"
#include "gmssl/zuc.h"
#include "gmssl/mem.h"
#define OK 1
#define FAILED 2

int gmssl_do_sm2Enc(  uint8_t* in_data, int in_datalen,
                      uint8_t* pubKey, int in_pubKeyLen
){
    LOGE("***********************SM2加密***************************");
    SM2_KEY sm2_key= {0};
//    memcpy(sm2_key.public_key.x,pubKey,32);
//    memcpy(sm2_key.public_key.y,pubKey + 32,32);

    sm2_key_generate(&sm2_key);
    printHex("sm2_key pubKey x",sm2_key.public_key.x,32);
    printHex("sm2_key pubKey y" ,sm2_key.public_key.y,32);
    printHex("sm2_key private_key" ,sm2_key.private_key,32);

    uint8_t  out_data[256] = {0};
    size_t out_datalen = 256;

    int ret = sm2_encrypt(&sm2_key, in_data, in_datalen, out_data, &out_datalen);
    LOGE("sm2_encrypt  ret==========>%d",ret);
    if(ret == OK){
        printHex("sm2_encrypt result:",out_data,out_datalen);
    }

    uint8_t  dec_data[256] = {0};
    size_t dec_datalen = 256;
    ret = sm2_decrypt(&sm2_key, out_data, out_datalen, dec_data,  &dec_datalen);
    if(ret==OK){
        printHex("sm2_decrypt result:",dec_data,dec_datalen);
    }

    return ret;

}



int gmssl_sm2_verifySign(
        uint8_t* in_data, int in_datalen,
        uint8_t* in_r, int in_rlen ,
        uint8_t* in_s, int in_slen,
        uint8_t* in_pubKey, int in_pubKeyLen
        ){
    LOGE("***********************PC工具签名，GMSSL验签***************************");
    uint8_t* data = in_data;
    int datalen = in_datalen;
    uint8_t* r = in_r;
    int rlen  = in_rlen;

    uint8_t* s = in_s;
    int slen = in_slen;

    uint8_t* pubKey =  in_pubKey;
    int pubKeyLen = in_pubKeyLen;

    uint8_t digest[32]= {0};
    printHex("data :",data,datalen);
    sm3_digest(data, datalen, digest);
    printHex("sm3_digest :",digest,32);

    SM2_KEY sm2_key= {0};
    memcpy(sm2_key.public_key.x,pubKey,32);
    memcpy(sm2_key.public_key.y,pubKey + 32,32);
    printHex("sm2_key pubKey x",sm2_key.public_key.x,32);
    printHex("sm2_key pubKey y" ,sm2_key.public_key.y,32);


    SM2_SIGNATURE  sig = {0};
    memcpy(sig.r,r,rlen);
    memcpy(sig.s,s,slen);
    printHex("sm2_key r",sig.r,32);
    printHex("sm2_key s" ,sig.s,32);

    int ret = sm2_do_verify(&sm2_key,digest,&sig);
    LOGE("sm2_do_verify ：%d",ret);
    LOGE("********************************************");
    return ret;

}

int gmssl_sm2_do_sign(  uint8_t* in_data, int in_datalen
){
    LOGE("***********************GMSSL签名，PC工具验签***************************");
    uint8_t* data = in_data;
    int datalen = in_datalen;
    int ret ;

    uint8_t digest[32]= {0};
    printHex("data :",data,datalen);
    sm3_digest(data, datalen, digest);
    printHex("sm3_digest :",digest,32);

    SM2_KEY sm2_key= {0};
    LOGE("*****************sm2 生成密钥对***************************");
    ret = sm2_key_generate(&sm2_key);
    LOGE("sm2_key_generate ret :%d",ret);
    printHex("sm2_key pubKey x",sm2_key.public_key.x,32);
    printHex("sm2_key pubKey y" ,sm2_key.public_key.y,32);

    SM2_SIGNATURE  sig = {0};
    uint8_t  sigbuf[128];
    size_t  siglen  = 128;
    ret = sm2_sign(&sm2_key,digest,  sigbuf,  &siglen);
    if(ret == OK){
        printHex("sm2_sign",sigbuf,  siglen);
    }

    LOGE("*****************sm2 签名***************************");
    ret = sm2_do_sign(&sm2_key,digest,&sig);
    LOGE("sm2_do_sign ret :%d",ret);
    if(ret == OK){
        printHex("sm2_do_sign r",sig.r,32);
        printHex("sm2_do_sign s" ,sig.s,32);
    }

    LOGE("*****************sm2 验签***************************");

    ret = sm2_do_verify(&sm2_key,digest,&sig);
    LOGE("sm2_do_verify ：%d",ret);
    LOGE("********************************************");
    return ret;

}


/*
 * SM2
 * http://www.gmbz.org.cn/main/viewfile/20180108023602687857.html
 * */
extern "C" JNIEXPORT jint JNICALL
Java_com_wzw_gmssldemo_MainActivity_sm2test(
        JNIEnv* env,
        jobject obj,
        jbyteArray jdata,jint jdataLen,
        jbyteArray jpubKey,jint jpubKeyLen,
        jbyteArray jr,jint jrLen,
        jbyteArray js,jint jsLen
        ) {
    int ret = 0;
    uint8_t* data = (uint8_t*)env->GetByteArrayElements(jdata, JNI_FALSE);
    int dataLen = jdataLen;
    printHex("data",data,dataLen);

    uint8_t* pubKey = (uint8_t*)env->GetByteArrayElements(jpubKey, JNI_FALSE);
    int pubKeyLen = jpubKeyLen;
//    printHex("pubKey",pubKey,pubKeyLen);

    uint8_t* r = (uint8_t*)env->GetByteArrayElements(jr, JNI_FALSE);
    int rLen = jrLen;
//    printHex("r",r,rLen);

    uint8_t* s = (uint8_t*)env->GetByteArrayElements(js, JNI_FALSE);
    int sLen = jsLen;


    gmssl_do_sm2Enc(data,dataLen,pubKey,pubKeyLen);

//    printHex("s",s,sLen);
//    gmssl_sm2_verifySign(data,dataLen,r,rLen,s,sLen,pubKey,pubKeyLen);

    gmssl_sm2_do_sign(data,dataLen);


    env->ReleaseByteArrayElements(jdata, reinterpret_cast<jbyte *>(data), JNI_FALSE);
    env->ReleaseByteArrayElements(jr, reinterpret_cast<jbyte *>(r), JNI_FALSE);
    env->ReleaseByteArrayElements(js, reinterpret_cast<jbyte *>(s), JNI_FALSE);
    env->ReleaseByteArrayElements(jpubKey, reinterpret_cast<jbyte *>(pubKey), JNI_FALSE);

    return ret;

}

extern "C" JNIEXPORT jint JNICALL
Java_com_wzw_gmssldemo_MainActivity_sm4Test(
        JNIEnv* env,
        jobject obj,
        jbyteArray jdata,jint jdataLen,
        jbyteArray jsm4Key,jint jsm4KeyLen
) {
    LOGE("***********************SM4 加解密测试***************************");
    int ret = 0;
    uint8_t* data = (uint8_t*)env->GetByteArrayElements(jdata, JNI_FALSE);
    int dataLen = jdataLen;
    printHex("data",data,dataLen);

    uint8_t* sm4Key = (uint8_t*)env->GetByteArrayElements(jsm4Key, JNI_FALSE);
    int sm4KeyLen = jsm4KeyLen;
    printHex("sm4Key",sm4Key,sm4KeyLen);

    SM4_KEY sm4key  ;
    /*encrypt*/
    {
        const uint8_t in[16] = {0};
        memcpy((void *) in, data, dataLen);

        uint8_t user_key[16] = {0};
        memcpy((void *) user_key, sm4Key, sm4KeyLen);
        sm4_set_encrypt_key(&sm4key, user_key);

        /*ECB*/
        uint8_t out[16] = {0};
        sm4_encrypt(&sm4key, in, out);
        printHex("sm4_encrypt[ECB]:", out, 16);
    }

/*CBC*/
    {
        uint8_t iv[16]  = {0}  ;
        memset(iv,0x11,16);
        printHex("iv:",iv,16);
        uint8_t out[256]  = {0}  ;
        size_t  outLen = 256;

        uint8_t user_key[16] = {0};
        memcpy((void *) user_key, sm4Key, sm4KeyLen);
        sm4_set_encrypt_key(&sm4key, user_key);
        /*NoPadding*/
        {
//            sm4_cbc_encrypt(&sm4key, iv, data, dataLen,  out );
//            outLen = 16;
        }
        /*PKCS5*/
        sm4_cbc_padding_encrypt(&sm4key, iv, data, dataLen,  out,&outLen);
        printHex("sm4_cbc_encrypt[CBC]:",out,outLen);
    }


    env->ReleaseByteArrayElements(jdata, reinterpret_cast<jbyte *>(data), JNI_FALSE);
    env->ReleaseByteArrayElements(jsm4Key, reinterpret_cast<jbyte *>(sm4Key), JNI_FALSE);
    return 0;

}


extern "C" JNIEXPORT jint JNICALL
Java_com_wzw_gmssldemo_MainActivity_sm2ParseCert(
        JNIEnv* env,
        jobject obj,
        jbyteArray jdata,jint jdataLen
) {
    LOGE("***********************SM2 证书解析 测试***************************");
    int ret = 0;
    const uint8_t *data = (uint8_t*)env->GetByteArrayElements(jdata, JNI_FALSE);
    int dataLen = jdataLen;
    printHex("data",data,dataLen);


    int  version = 0;
    uint8_t   serial_number[256] = {0};
    size_t  serial_number_len  = 256;
    int  inner_signature_algor = 0;

    uint8_t   issuer[256] = {0};
    size_t  issuer_len  = 256;
    time_t not_before;
    time_t not_after;

    uint8_t   subject[256] = {0};
    size_t  subject_len  = 256;

    SM2_KEY  subject_public_key;

    uint8_t issuer_unique_id[128] = {0};
    size_t issuer_unique_id_len = 128;

    uint8_t subject_unique_id[128] = {0};
    size_t subject_unique_id_len = 128;

    uint8_t extensions[128] = {0};
    size_t extensions_len = 128;

    int signature_algor = 0;

    uint8_t signature[128] = {0};
    size_t signature_len = 128;

    ret =  x509_cert_get_details(
                                data,dataLen,
                                 &version,
                                 reinterpret_cast<const uint8_t **>(serial_number), &serial_number_len,
                                 &inner_signature_algor,
                                 reinterpret_cast<const uint8_t **>(&issuer), &issuer_len,
                                 &not_before, &not_after,
                                 reinterpret_cast<const uint8_t **>(&subject), &subject_len,
                                 &subject_public_key,
                                 reinterpret_cast<const uint8_t **>(&issuer_unique_id), &issuer_unique_id_len,
                                 reinterpret_cast<const uint8_t **>(&subject_unique_id), &subject_unique_id_len,
                                 reinterpret_cast<const uint8_t **>(&extensions), &extensions_len,
                                 &signature_algor,
                                 reinterpret_cast<const uint8_t **>(&signature), &signature_len);
    if(ret == OK){
        LOGE("x509_cert_get_details  ret========>%d",ret);
        LOGE("not_before==========>%d",not_before);
        LOGE("not_after==========>%d",not_after);
        printHex("public_key x:",subject_public_key.public_key.x,32);
        printHex("public_key y: ",subject_public_key.public_key.y,32);
    }

    env->ReleaseByteArrayElements(jdata, (jbyte*)data, JNI_FALSE);
    return ret;
}


/*
*SM9 标准文档
*https://www.math.pku.edu.cn/teachers/qiuzy/qfiles/SM9.pdf
* */
int gmssl_sm9test(){
    LOGE("***********************SM9 测试***************************");
    int ret  ;
    SM9_ENC_MASTER_KEY master;/*主密钥*/
    SM9_ENC_MASTER_KEY master_public;
    SM9_ENC_KEY key;/*用户加密密钥*/
    const char *id = "Alice";
    uint8_t buf[512]= {0};
    uint8_t*  p  = buf;
    const uint8_t *cp = p;
    size_t len;
    char mbuf[256] = {0};
    size_t mlen;

    /*加密主密钥生成函数：
     * 随机生成主私钥 master，计算对应的主公钥Ppube并将二者写入给定的加密主密钥结构master中
     * */
    sm9_enc_master_key_generate(&master);
    /*根据给定的用户标识信息字符串id及其长度idlen，
    *基于给定的加密主密钥master计算出用户对应的加密密钥，并写入加密密钥结构key中
     * */
    sm9_enc_master_key_extract_key(&master, id, strlen(id), &key);

    sm9_enc_master_public_key_to_der(&master, (uint8_t **) &p, &len);
//    printHex("sm9_enc_master_public_key_to_der p:",p,len);
    sm9_enc_master_public_key_from_der(&master_public, &cp, &len);
//    printHex("sm9_enc_master_public_key_from_der cp:",cp,len);


    const char* msg = "SM9 test";
    LOGE("sm9  plaintext:%s", msg);
    sm9_encrypt(&master_public, id, strlen(id), (uint8_t *)msg, strlen(msg), buf, &len);
//    sm9_encrypt(&master, id, strlen(id), (uint8_t *)msg, strlen(msg), buf, &len);
    printHex("sm9_encrypt result:",buf,len);

    ret = sm9_decrypt(&key, id, strlen(id), buf, len, (uint8_t *)mbuf, &mlen);
    if (ret != OK) {
        LOGE(  "sm9_decrypt failed\n");
        return FAILED;
    }
    mbuf[mlen] = 0;
    LOGE("sm9_decrypt result:%s", mbuf);
    return OK ;
}

extern "C" JNIEXPORT jint JNICALL
Java_com_wzw_gmssldemo_MainActivity_sm9test(
        JNIEnv* env,
        jobject obj
) {
    int ret = gmssl_sm9test();
    return ret;
}

/*
* ZUC标准文档
* http://c.gb688.cn/bzgk/gb/showGb?type=online&hcno=8C41A3AEECCA52B5C0011C8010CF0715
* */
int gmssl_zuctest(){
    LOGE("***********************ZUC 测试***************************");
    ZUC_CTX zuc_ctx;
    uint8_t key[16] = {
            0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,
            0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,
    };
    uint8_t iv[16] = {
            0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,
            0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,
    };
    uint8_t* inbuf  = (uint8_t *) "ZUC test";
    uint8_t encBuf[128] = {0};
    size_t enclen = 128;
    LOGE("***********************ZUC加密***************************");
    LOGE("ZUC  plaintext:%s", inbuf);
    {
        if (zuc_encrypt_init(&zuc_ctx, key, iv) != OK) {
            return FAILED;
        }
        /*while ((inlen = fread(inbuf, 1, sizeof(inbuf), stdin)) > 0) {
            if (zuc_encrypt_update(&zuc_ctx, inbuf, inlen, outbuf, &outlen) != 1) {
                LOGE("zuc_encrypt_update  %d",ret);
                return 1;
            }
        }*/
        if (zuc_encrypt_update(&zuc_ctx, inbuf, strlen((const char *) inbuf), encBuf, &enclen) != OK) {
            return FAILED;
        }

//         if (zuc_encrypt_finish(&zuc_ctx, encBuf, &enclen) != 1) {
//            LOGE("zuc_encrypt_finish  %d",ret);
//            return 1;
//        }
        LOGE("zuc_encrypt_finish outlen : %d",enclen);
        printHex("zuc_encrypt result:",encBuf,enclen);
    }
    LOGE("***********************ZUC解密***************************");

    {
        uint8_t  decBuf[128] = {0};
        size_t decBufLen = 128;

        if (zuc_decrypt_init(&zuc_ctx, key, iv) != OK) {
            return FAILED;
        }
        /*while ((inlen = fread(inbuf, 1, sizeof(inbuf), stdin)) >l 0) {
            if (zuc_encrypt_update(&zuc_ctx, inbuf, inlen, outbuf, &outlen) != 1) {
                LOGE("zuc_encrypt_update  %d",ret);
                return 1;
            }
        }*/
        if (zuc_decrypt_update(&zuc_ctx, encBuf,enclen, decBuf, &decBufLen) != OK) {
            return FAILED;
        }

        if (zuc_decrypt_finish(&zuc_ctx, decBuf,  &decBufLen) != OK) {
            return FAILED;
        }

        LOGE("zuc_decrypt  result:%s",decBuf);
 }
    return OK ;
}


extern "C" JNIEXPORT jint JNICALL
Java_com_wzw_gmssldemo_MainActivity_zuctest(
        JNIEnv* env,
        jobject obj
) {
    int ret = gmssl_zuctest();
    return ret;
}