class JJsonnet {

    //   private native void print();
    private native String evaluateSnippet(String str);
    private native String evaluateFile(String fileName);

    public static void main(String[] args) {
        //   new HelloWorld().print();
        String jsonStr = "{\n" +
                "    person1: {\n" +
                "        name: \"Alice\",\n" +
                "        welcome: \"Hello \"  + \"!\",\n" +
                //"        welcome: \"Hello \" + self.name + \"!\",\n" +
                "    },\n" +
                //"    person2: self.person1 { name: \"Bob\" },\n" +
                //"    person2: self.person1 { name: std.extVar(\"OTHER_NAME\") },\n" +
                "}";
        jsonStr = "{}";
        String xxx = new JJsonnet().evaluateFile("test.jsonnet");
        // String xxx = new JJsonnet().evaluateSnippet(jsonStr);
        System.out.println(xxx);
    }

    static {
        System.loadLibrary("jjsonnet");
    }
}
