import javax.crypto.Cipher;
import javax.crypto.spec.IvParameterSpec;
import javax.crypto.spec.SecretKeySpec;
import java.util.Base64;

public class crypt_aes {
	private final static String key = "dsfn";
	private final static String iv = "Data-AID";
	
    public static void main(String[] args) {
		
		if(args.length < 1) usage();
		
		String cryptType = args[0];
		String inputText = args[1], outputText = "";
		
		if		(cryptType.equals("ENC"))
		{
			outputText = encrypt(inputText);
		}
		else if	(cryptType.equals("DEC"))
		{
			outputText = decrypt(inputText);
		}
		else
			usage();
		
		System.out.println(" input : "+ inputText);
		System.out.println("output : "+ outputText);
		
    }// main
	
	public static void usage()
	{
		System.out.println("java crypt_aes <ENC|DEC> <text>");
		System.exit(1);
	};
	
	public static byte[] getKey()
	{
		return getBytes(key, 32);
	};
	
	public static byte[] getIV()
	{
		return getBytes(iv, 16);
	};
	
	public static byte[] getBytes(String data, int length)
	{
		byte[] retval = new byte[length];
		byte[] byteData = data.getBytes();
		
		System.arraycopy(byteData, 0, retval, 0, byteData.length < length ? byteData.length : length);
		return retval;
	};
	
	public static String encrypt(String plainText)
	{
		String retval = "";
		
		try
		{
			byte[] byteKey = getKey();
			byte[] byteIV = getIV();
			
			SecretKeySpec keySpec = new SecretKeySpec(byteKey, "AES");
			IvParameterSpec ivParamSpec = new IvParameterSpec(byteIV);
		
			Cipher cipher = Cipher.getInstance("AES/CBC/PKCS5Padding");
			cipher.init(Cipher.ENCRYPT_MODE, keySpec, ivParamSpec);
		
			byte[] encrypted = cipher.doFinal(plainText.getBytes());
			retval = Base64.getEncoder().encodeToString(encrypted);
		}
		catch (Exception e)
		{
			System.out.println("aes encrypt fail");
			e.printStackTrace();
		};
		
		return retval;
	};
	
	public static String decrypt(String encryptText)
	{
		String retval = "";
		
		try
		{
			byte[] decodedEncryptedText = Base64.getDecoder().decode(encryptText);
			
			byte[] byteKey = getKey();
			byte[] byteIV = getIV();
			
			SecretKeySpec keySpec = new SecretKeySpec(byteKey, "AES");
			IvParameterSpec ivParamSpec = new IvParameterSpec(byteIV);
		
			Cipher cipher = Cipher.getInstance("AES/CBC/PKCS5Padding");
			cipher.init(Cipher.DECRYPT_MODE, keySpec, ivParamSpec);
		
			byte[] encrypted = cipher.doFinal(decodedEncryptedText);
			retval = new String(encrypted);
		}
		catch (Exception e)
		{
			System.out.println("aes decrypt fail");
			e.printStackTrace();
		};
		
		return retval;
	};
}
