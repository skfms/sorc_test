import java.sql.Connection;
import java.sql.DriverManager;

public class jdbc_oracle {
    public static void main(String[] args) {
        // 1. DB접속
        // -Connection 클래스
        Connection conn = null;
 
		if(args.length < 3) usage();
 
        // 2. 연결 문자열 생성
        // -접속에 필요한 정보로 구성된 문자열, Connection String
        //String url = "jdbc:oracle:thin:@192.168.219.126:15121:orclcdb"; //localhost대신 ip주소가 들어갈수도
        //String id = "dac";
        //String pw = "dacpwd";
		
		String url = args[0];
		String id  = args[1];
		String pw  = args[2];
 
        // DB작업 > 외부 입출력 > try-catch 필수
 
        try {
            // 3. JDBC 드라이버 로딩
            Class.forName("oracle.jdbc.driver.OracleDriver");
 
            // 4. 접속
            // - Connection 객체 생성 + 접속 작업.
            conn = DriverManager.getConnection(url, id, pw);
            System.out.println(conn.isClosed()?"Connect Fail !":"Connect Ok !");// 접속중(false), 접속종료(true)
 
            // 5. SQL
 
            // 6. 접속종료
            conn.close();
 
        } catch (Exception e) {
            e.printStackTrace();
        }
    }// main
	
	public static void usage()
	{
		System.out.println("java -cp jodbc?.jar jdbc_oracle <jdbc_connect_string> <uid> <pwd>");
		System.exit(1);
	};
}
