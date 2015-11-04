public class swig_example_java {
	public static void main(String argv[]) {
		System.loadLibrary("configctlJava");
		configctl ctx = new configctl();
		try {
			configctlJava.initConfigctl(ctx, "../tests/config/hello.xml", "../tests/config/hello@2015-06-08.yin", "../tests/config");
		} catch (Exception e) {
			System.out.println(e.getMessage());
		}

		try {
			String result = configctlJava.getConfigctlString(ctx, "hello/foo");
			System.out.println("get hello/foo -> " + result);
		} catch (Exception e) {
			System.out.println(e.getMessage());
		}

		try {
			int result = configctlJava.getConfigctlInt32(ctx, "hello/bar_error");
			System.out.println(result);
		} catch (Exception e) {
			System.out.println("Success: Exception is thrown for geting non existing data!");
		}

		try {
			int result = configctlJava.getConfigctlInt32(ctx, "hello/bar");
			System.out.println("get hello/bar -> " + result);
		} catch (Exception e) {
			System.out.println(e.getMessage());
		}

		try {
			configctlJava.setConfigctlInt8(ctx, "hello/number8", 123456);
			int result = configctlJava.getConfigctlInt8(ctx, "hello/number8");
			System.out.println(result);
		} catch (Exception e) {
			System.out.println("Success: Exception is thrown for seting integer out of range!");
		}

		try {
			configctlJava.setConfigctlInt8(ctx, "hello/number8", 123);
			int result = configctlJava.getConfigctlInt8(ctx, "hello/number8");
			System.out.println("get hello/number8 -> " + result);
		} catch (Exception e) {
			System.out.println(e.getMessage());
		}

		try {
			configctlJava.deleteConfigctlElement(ctx, "hello/foo");
			String result = configctlJava.getConfigctlString(ctx, "hello/foo");
			System.out.println(result);
		} catch (Exception e) {
			System.out.println("Success: Exception is thrown for trying to get a node which was previously deleted!");
		}

		try {
			configctlJava.destroyConfigctl(ctx);
		} catch (Exception e) {
			System.out.println(e.getMessage());
		}

	}
}
