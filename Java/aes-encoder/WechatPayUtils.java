import javax.crypto.Cipher;
import javax.crypto.spec.IvParameterSpec;
import javax.crypto.spec.SecretKeySpec;

import org.apache.commons.codec.binary.Base64;
import org.apache.commons.codec.binary.Hex;

/**
 * 微信实名认证接口工具类
 */
public class WechatPayUtils {
	/**
	 * AES使用128位的 AES-CBC模式对请求数据进行加密
	 * @param orginal 待加密字符串
	 * @param aesKey 加密密钥
	 * @param iv 初始化向量
	 * @return
	 * @throws
	 */
    public static String encrypt(String orginal, String aesKey, String iv) throws Exception {
    	try {
    		//密钥先进行 Hex 解码
    		byte[] encodeFormat = Hex.decodeHex(aesKey.toCharArray());
    		
			Cipher cipher = Cipher.getInstance("AES/CBC/PKCS5Padding");
			SecretKeySpec skeySpec = new SecretKeySpec(encodeFormat, "AES");
			cipher.init(Cipher.ENCRYPT_MODE, skeySpec, new IvParameterSpec(iv.getBytes("UTF-8")));
			byte[] encrypted = cipher.doFinal(orginal.getBytes());

			return new Base64().encodeBase64String(encrypted);
		} catch (Exception e) {
			e.printStackTrace();
		}
		return null;
    }

    
    /**
     * AES使用128位的 AES-CBC模式对返回数据进行解密
     * @param encrypted 目标密文（base64编码）
     * @param aesKey 解密密钥
     * @param iv 初始化向量
     * @throws Exception
     */
    public static String decrypt(String encrypted, String aesKey, String iv){
    	try {
    		//密钥先进行Hex解码
    		byte[] encodeFormat = Hex.decodeHex(aesKey.toCharArray());
    		
			Cipher cipher = Cipher.getInstance("AES/CBC/PKCS5Padding");
			SecretKeySpec keySpec = new SecretKeySpec(encodeFormat, "AES");
			cipher.init(Cipher.DECRYPT_MODE, keySpec, new IvParameterSpec(iv.getBytes("UTF-8")));
			byte[] decbbdt = cipher.doFinal(Base64.decodeBase64(encrypted));

			return new String(decbbdt);
		} catch (Exception e) {
			e.printStackTrace();
		}
		return null;
    }
    
	public static void main(String[] args) throws Exception {
		String orginal = "name=titus&id_code=420583190000000000&bill_no=12#34#56#78";
		String aesKey = "111111b06b9f739b950ddb41db2690d";
		String iv = "0000000000000000";
		System.out.println("加密后："+encrypt(orginal, aesKey, iv));
		System.out.println("解密后："+decrypt(encrypt(orginal, aesKey, iv), aesKey, iv));

	}
}