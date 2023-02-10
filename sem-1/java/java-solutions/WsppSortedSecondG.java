import java.io.*;
import java.nio.charset.StandardCharsets;
import java.util.*;

class Cell {
    IntList myList;
    int counter;
    int cntWordInLines;

    public Cell(IntList myList, int ans, int cntWordInLines) {
        this.myList = myList;
        this.counter = ans;
        this.cntWordInLines = cntWordInLines;
    }
}

public class WsppSortedSecondG {

    public static void main(String[] args) {

        TreeMap<String, Cell> statWorld = new TreeMap<>();
        int cnt = 0;
        List<String> wasInLastLine = new ArrayList<>();
        MyScan6 scanFile = new MyScan6(args[0]);
        while (scanFile.hasNext()) {
            MyScan6 scanStr = new MyScan6(scanFile.nextLine());
            for (String e : wasInLastLine) {
                statWorld.put(e, new Cell(statWorld.get(e).myList, statWorld.get(e).counter, 0));
            }
            while (scanStr.hasNext()) {
                String str = scanStr.nextItem().toLowerCase();
                if (!str.isEmpty()) {
                    if (!statWorld.containsKey(str)) {
                        statWorld.put(str, new Cell(new IntList(), 1, 1));
                        wasInLastLine.add(str);
                    } else {
                        Cell now = statWorld.get(str);
                        if (now.cntWordInLines % 2 == 1) {
                            now.myList.add(cnt);
                        }
                        now.cntWordInLines++;
                        now.counter++;
                        statWorld.put(str, now);
                    }
                    cnt++;
                }
            }
        }
        scanFile.close();
        try {
            Writer writer = new OutputStreamWriter(new FileOutputStream(args[1]), StandardCharsets.UTF_8.name());
            try {
                for (Map.Entry<String, Cell> x : statWorld.entrySet()) {
                    writer.write(x.getKey() + " " + x.getValue().counter);
                    for (int j = 0; j < x.getValue().myList.size(); j++) {
                        writer.write(" " + (Integer) (x.getValue().myList.get(j) + 1));
                        //System.err.println((Integer) (x.getValue().myList.get(j) + 1));
                    }
                    writer.write(System.lineSeparator());
                }
            } finally {
                writer.close();
            }
        } catch (
                ArrayIndexOutOfBoundsException e) {
            System.out.println("Write name input and output file in cmd line \n" + e.getMessage());
        } catch (
                FileNotFoundException e) {
            System.out.println("File not Found \n" + e.getMessage());
        } catch (
                IOException e) {
            System.out.println(e.getMessage());
        }
    }
}

//javac WsppSortedSecondG.java
//java WsppSortedSecondG input.txt output.txt
// java -jar WsppSortedSecondGTest.jar

