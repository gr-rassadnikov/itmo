import java.io.*;
import java.util.*;
import java.lang.*;
import java.nio.charset.StandardCharsets;


public class Wspp {

    public static boolean isWord(int ch) {
        return Character.isLetter((char) ch) || ch == 39 ||
                Character.DASH_PUNCTUATION == Character.getType((char) ch);
    }

    public static void main(String[] args) {

        String[] Words = new String[1];
        HashMap<String, IntList> StatWorld = new HashMap<>();
        int countWord = 0;
        int cnt = 0;
        try {
            BufferedReader reader = new BufferedReader(new InputStreamReader(new FileInputStream(args[0]), StandardCharsets.UTF_8.name()));
            try {
                StringBuilder stringBuilder = new StringBuilder();
                int ch;
                while ((ch = reader.read()) != -1) {
                    if (isWord(ch)) {
                        stringBuilder.append((char) ch);
                    } else {
                        String str = stringBuilder.toString();
                        if (str != "") {
                            str = str.toLowerCase();
                            if (!StatWorld.containsKey(str)) {
                                IntList m = new IntList();
                                m.add(cnt);
                                StatWorld.put(str, m);
                                if (Words.length == countWord) {
                                    Words = Arrays.copyOf(Words, 2 * countWord);
                                }
                                Words[countWord] = str;
                                countWord++;
                            } else {
                                IntList m = StatWorld.get(str);
                                m.add(cnt);
                                StatWorld.put(str, m);
                            }
                            cnt++;
                            stringBuilder = new StringBuilder();
                        }
                    }
                }
            } finally {
                reader.close();
            }
            Writer writer = new OutputStreamWriter(new FileOutputStream(args[1]), StandardCharsets.UTF_8.name());
            try {
                for (int i = 0; i < countWord; i++) {
                    IntList x = StatWorld.get(Words[i]);
                    writer.write(Words[i] + " " + x.size());
                    for (int j = 0; j < x.size(); j++) {
                        Integer h = x.get(j) + 1;
                        writer.write(" " + h);
                    }
                    writer.write("\n");
                }
            } finally {
                writer.close();
            }
        } catch (ArrayIndexOutOfBoundsException e) {
            System.out.println("Write name input and output file in cmd line \n" + e.getMessage());
        } catch (FileNotFoundException e) {
            System.out.println("File not Found \n" + e.getMessage());
        } catch (IOException e) {
            System.out.println(e.getMessage());
        }
    }
}
//javac Wspp.java
//java Wspp input.txt output.txt
// java -jar WsppTest.jar