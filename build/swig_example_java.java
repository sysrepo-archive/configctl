public class main {
	public static void main(String argv[]) {
		System.loadLibrary("configctl_java");
		configctl ctx = configctl_java.configctl_create();
		configctl_java.configctl_init(ctx, "../tests/config/hello.xml", "../tests/config/hello@2015-06-08.yin", "../tests/config");
		String result = configctl_java.configctl_get_string(ctx, "hello/foo");
		System.out.println(result);
	}
}
