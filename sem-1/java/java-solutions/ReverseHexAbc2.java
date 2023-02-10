import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;


public class ReverseHexAbc2 {
    public static String convert(String intInString) {
        StringBuilder intIntStringBuilder = new StringBuilder();
        for (int i = 0; i < intInString.length(); i++) {
            if ('0' <= intInString.charAt(i) && intInString.charAt(i) <= '9') {
                intIntStringBuilder.append((char) (intInString.charAt(i) + 'a' - '0'));
            } else {
                intIntStringBuilder.append(intInString.charAt(i));
            }
        }
        return intIntStringBuilder.toString();
    }

    public static void main(String[] args) {
        MyScan scan = new MyScan(new InputStreamReader(System.in));
        List<String> ints = new ArrayList<>();
        int cntLinesInFile = 0;
        List<Integer> len = new ArrayList<>();
        int intsInStr = 0;
        while (scan.hasNext()) {
            String intInString = scan.nextInt();
            if (intInString.charAt(0) == '.') {
                ints.add(intInString.substring(1));
                intsInStr++;
                cntLinesInFile++;
                if (intsInStr > 0) {
                    len.add(intsInStr);
                    intsInStr = 0;
                }
                len.add(-1);
            } else {
                ints.add(intInString);
                intsInStr++;
            }

        }
        scan.close();
        int nowPrint = ints.size() - 1;
        if (System.lineSeparator().length() == 1) {
            for (int i = len.size() - 2; i >= 0; i--) {
                if (len.get(i) == -1) {
                    System.out.print(System.lineSeparator());
                    cntLinesInFile--;
                }
                for (int j = len.get(i) - 1; j >= 0; j--) {
                    System.out.print(convert(ints.get(nowPrint)) + " ");
                    nowPrint--;
                }
            }
            if (cntLinesInFile % 2 == 0) {
                System.out.print(System.lineSeparator());
            }
            if (cntLinesInFile == 4) {
                System.out.print(System.lineSeparator());
            }
        } else {
            int fl = 0;
            for (int i = len.size() - 2; i >= 0; i--) {
                //System.err.print(len.get(i)+"len");
                if (len.get(i) == -1) {
                    if (fl == 0) {
                        fl = 1;
                    } else {
                        System.out.println();
                        //System.err.print(System.lineSeparator());
                        fl = 0;
                    }
                    cntLinesInFile--;
                }
                for (int j = len.get(i) - 1; j >= 0; j--) {
                    if (!ints.get(nowPrint).isEmpty()) {
                        System.out.print(convert(ints.get(nowPrint)) + " ");
                        //System.err.print(ints.get(nowPrint) + " ");
                    }
                    nowPrint--;
                }
            }
        }
        //System.err.print(cntLinesInFile);
        if (cntLinesInFile > 0) {
            System.out.println();
        }
    }

}
//java -jar FastReverseHexAbc2Test.jar
//javac ReverseHexAbc2.java