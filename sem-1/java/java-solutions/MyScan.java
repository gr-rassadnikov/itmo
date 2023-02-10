import java.io.*;
import java.lang.*;
import java.util.Arrays;

class MyScan {
    String nameFile;
    Reader reader;
    String str;
    int indInStr = 0;
    int ch;
    char[] buffer = new char[2048];
    int indInBuffer = buffer.length;


    public int getCh() {
        try {
            if (indInBuffer == buffer.length) {
                for (int i = 0; i < buffer.length; i++) {
                    buffer[i] = 0;
                }
                if (reader.read(buffer) == -1) {
                    return -1;
                }
                indInBuffer = 0;
            }
            if ((int) buffer[indInBuffer] == 0) {
                indInBuffer++;
                return -1;
            }
            //System.err.print(buffer[indInBuffer]+"gc");
            return buffer[indInBuffer++];

        } catch (IOException e) {
            System.out.println(e.getMessage());
        }
        return 0;
    }

    public static boolean isInt(int ch) {
        return ((Character.isDigit(ch)) || (ch >= 'a' && ch <= 'k') || ch == '-' || ch == 'x' || ch == 'X');
    }

    public static boolean isWord(int ch) {
        return (Character.isLetter((char) ch) || ch == 39 ||
                Character.DASH_PUNCTUATION == Character.getType((char) ch) || ch == '\r' || ch == '\n');
    }

    public MyScan(InputStreamReader nameIn) {
        this.reader = nameIn;
    }

    public MyScan(String nameFile) {
        this.nameFile = nameFile;
        try {
            this.reader = new InputStreamReader(new FileInputStream(nameFile), "utf-8");
        } catch (FileNotFoundException e) {
            this.str = nameFile;
        } catch (IOException e) {
            System.out.println(e.getMessage());
        }
    }


    public String nextInt() {
        StringBuilder strBuilder = new StringBuilder("");

        while (true) {
            if (ch == '\r' || ch == '\n') {
                //System.err.println("rrr");
                if (strBuilder.toString().length() > 0 && (strBuilder.toString().charAt(0) == '\n'
                        || strBuilder.toString().charAt(0) == '\r')) {
                    return ".";
                }
                String intInString = strBuilder.toString();
                if (intInString.startsWith("0x") || intInString.startsWith("0X")) {
                    intInString = Long.toString((int) Long.parseLong(intInString.substring(2), 16));
                }
                //System.err.print(intInString);
                return "." + intInString;
            }
            if (strBuilder.toString().length() > 0 && !isInt(ch)) {
                break;
            }
            if (isInt(ch)) {
                strBuilder.append((char) ch);
            }
            ch = getCh();
        }
        String intInString = strBuilder.toString();
        if (intInString.startsWith("0x") || intInString.startsWith("0X")) {
            intInString = Long.toString((int) Long.parseLong(intInString.substring(2), 16));
        }
        //System.err.print(intInString);
        return intInString;
    }

    public boolean hasNext() {

        this.ch = getCh();
        if (this.ch == -1) {
            return false;
        }
        return true;
    }

    public void close() {
        try {
            this.reader.close();
        } catch (IOException e) {
            System.out.println(e.getMessage());
        }
    }
}


//javac FastScan.java
//ava WordStatCount input.txt output.txtj
//java -jar