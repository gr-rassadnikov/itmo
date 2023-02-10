import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class Reverse {

    public static void main(String[] args) {
        MyScan scan = new MyScan(new InputStreamReader(System.in));
        /*
        Scanner sc =new Scanner(System.in);
        Integer f= sc.nextInt();

         */
        List<String> ints = new ArrayList<>();
        int cntLinesInFile = 0;
        List<Integer> len = new ArrayList<>();
        int intsInStr = 0;
        /*
        ints.add(f.toString());
        intsInStr++;

         */
        while (scan.hasNext()) {
            String intInString = scan.nextInt();
            //System.err.println("-"+intInString+"-");

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


            //System.err.println(intInString);
        }
        scan.close();
        int nowPrint = ints.size() - 1;
        //len.add(intsInStr);
        //System.err.print(nowPrint+" -"+ len.size());
        if (System.lineSeparator().length() == 1) {
            for (int i = len.size() - 2; i >= 0; i--) {
                //System.err.print(len.get(i)+"len");
                if (len.get(i) == -1) {
                    System.out.print(System.lineSeparator());
                    cntLinesInFile--;
                }
                for (int j = len.get(i) - 1; j >= 0; j--) {
                    System.out.print(ints.get(nowPrint) + " ");
                    //System.err.print(ints.get(nowPrint) + " ");
                    nowPrint--;
                }
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
                        System.out.print(ints.get(nowPrint) + " ");
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