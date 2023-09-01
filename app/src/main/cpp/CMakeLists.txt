cmake_minimum_required(VERSION 3.10)

project("gmssldemo")

include_directories(
        # 通讯库头文件
        ${CMAKE_CURRENT_SOURCE_DIR}/gmssl/include/
        ${CMAKE_CURRENT_SOURCE_DIR}/log/
        ${CMAKE_CURRENT_SOURCE_DIR}/util/
)

add_library( # Sets the name of the library.
        gmssl

        # Sets the library as a shared library.
        SHARED

        # Provides a relative path to your source file(s).
        native-lib.cpp
        gmssl/src/version.c
        gmssl/src/debug.c
        gmssl/src/sm4_common.c
        gmssl/src/sm4_enc.c
        gmssl/src/sm4_modes.c
        gmssl/src/sm4_setkey.c
        gmssl/src/sm3.c
        gmssl/src/sm3_hmac.c
        gmssl/src/sm3_kdf.c
        gmssl/src/sm2_alg.c
        gmssl/src/sm2_key.c
        gmssl/src/sm2_lib.c
        gmssl/src/sm9_alg.c
        gmssl/src/sm9_key.c
        gmssl/src/sm9_lib.c
        gmssl/src/zuc.c
        gmssl/src/zuc_modes.c
        gmssl/src/aes.c
        gmssl/src/aes_modes.c
        gmssl/src/sha256.c
        gmssl/src/sha512.c
        gmssl/src/chacha20.c
        gmssl/src/hash_drbg.c
        gmssl/src/block_cipher.c
        gmssl/src/digest.c
        gmssl/src/hmac.c
        gmssl/src/hkdf.c
        gmssl/src/pbkdf2.c
        gmssl/src/gf128.c
        gmssl/src/gcm.c
        gmssl/src/aead.c
        gmssl/src/pkcs8.c
        gmssl/src/ec.c
        gmssl/src/rsa.c
        gmssl/src/asn1.c
        gmssl/src/hex.c
        gmssl/src/base64.c
        gmssl/src/pem.c
        gmssl/src/x509_alg.c
        gmssl/src/x509_cer.c
        gmssl/src/x509_ext.c
        gmssl/src/x509_req.c
        gmssl/src/x509_crl.c
        gmssl/src/x509_new.c
        gmssl/src/cms.c
        gmssl/src/sdf/sdf.c
        gmssl/src/sdf/sdf_lib.c
        gmssl/src/sdf/sdf_meth.c
        gmssl/src/sdf/sdf_ext.c
        gmssl/src/sdf/sdf_sansec.c
        gmssl/src/skf/skf.c
        gmssl/src/skf/skf_lib.c
        gmssl/src/skf/skf_meth.c
        gmssl/src/skf/skf_ext.c
        gmssl/src/skf/skf_prn.c
        gmssl/src/skf/skf_wisec.c
        gmssl/src/socket.c
        gmssl/src/tls.c
        gmssl/src/tls_ext.c
        gmssl/src/tls_trace.c
        gmssl/src/tlcp.c
        gmssl/src/tls12.c
        gmssl/src/tls13.c
        gmssl/src/file.c
        gmssl/src/rand.c
        gmssl/src/http.c
        log/log.cpp
        util/utils.cpp
        )


find_library( # Sets the name of the path variable.
        log-lib

        log)

target_link_libraries( # Specifies the target library.
        gmssl

        ${log-lib})