

#ifndef MTEncryption_H
#define MTEncryption_H

#import <Foundation/Foundation.h>

#ifdef __cplusplus
extern "C" {
#endif
    
NSData *MTSha1(NSData *data);
NSData *MTSubdataSha1(NSData *data, NSUInteger offset, NSUInteger length);
    
NSData *MTSha256(NSData *data);
    
void MTRawSha1(void const *inData, NSUInteger length, void *outData);
void MTRawSha256(void const *inData, NSUInteger length, void *outData);
    
int32_t MTMurMurHash32(const void *bytes, int length);
    
void MTAesEncryptInplace(NSMutableData *data, NSData *key, NSData *iv);
void MTAesEncryptInplaceAndModifyIv(NSMutableData *data, NSData *key, NSMutableData *iv);
void MTAesEncryptBytesInplaceAndModifyIv(void *data, NSInteger length, NSData *key, void *iv);
void MTAesEncryptRaw(void const *data, void *outData, NSInteger length, void const *key, void const *iv);
void MTAesDecryptRaw(void const *data, void *outData, NSInteger length, void const *key, void const *iv);
void MTAesDecryptInplaceAndModifyIv(NSMutableData *data, NSData *key, NSMutableData *iv);
void MTAesDecryptBytesInplaceAndModifyIv(void *data, NSInteger length, NSData *key, void *iv);
NSData *MTAesEncrypt(NSData *data, NSData *key, NSData *iv);
NSData *MTAesDecrypt(NSData *data, NSData *key, NSData *iv);
NSData *MTRsaEncrypt(NSString *publicKey, NSData *data);
NSData *MTExp(NSData *base, NSData *exp, NSData *modulus);
bool MTFactorize(uint64_t what, uint64_t *resA, uint64_t *resB);
    
NSData *MTAesCtrDecrypt(NSData *data, NSData *key, NSData *iv);
    
@protocol MTKeychain;
bool MTCheckIsSafeG(unsigned int g);
bool MTCheckIsSafePrime(NSData *numberBytes, id<MTKeychain> keychain);
bool MTCheckIsSafeGAOrB(NSData *gAOrB, NSData *p);
bool MTCheckMod(NSData *numberBytes, unsigned int g, id<MTKeychain> keychain);
    
@interface MTAesCtr : NSObject

- (instancetype)initWithKey:(const void *)key keyLength:(int)keyLength iv:(const void *)iv decrypt:(bool)decrypt;
- (instancetype)initWithKey:(const void *)key keyLength:(int)keyLength iv:(const void *)iv ecount:(void *)ecount num:(uint32_t)num;

- (uint32_t)num;
- (void *)ecount;
- (void)getIv:(void *)iv;

- (void)encryptIn:(const unsigned char *)in out:(unsigned char *)out len:(size_t)len;

@end
    
uint64_t MTRsaFingerprint(NSString *key);
    
NSData *MTRsaEncryptPKCS1OAEP(NSString *key, NSData *data);
    
@interface MTBackupDatacenterAddress : NSObject

@property (nonatomic, readonly) int32_t datacenterId;
@property (nonatomic, strong, readonly) NSString *ip;
@property (nonatomic, readonly) int32_t port;
@property (nonatomic, strong, readonly) NSData *secret;

@end

@interface MTBackupDatacenterData : NSObject

@property (nonatomic, readonly) int32_t timestamp;
@property (nonatomic, readonly) int32_t expirationDate;
@property (nonatomic, strong, readonly) NSArray<MTBackupDatacenterAddress *> *addressList;

@end

MTBackupDatacenterData *MTIPDataDecode(NSData *data, NSString *phoneNumber);

#ifdef __cplusplus
}
#endif

#endif
