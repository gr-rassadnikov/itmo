package md2html;

import java.io.FileInputStream;
import java.io.*;
import java.util.*;


class Parse {
    String str;
    StringBuilder getResult;
    int getInd;

    StringBuilder afterSlash(String str, StringBuilder ans, int ind) {
        if (str.charAt(ind) == '>') {
            ans.append("&gt;");
        } else if (str.charAt(ind) == '<') {
            ans.append("&lt;");
        } else if (str.charAt(ind) == '&') {
            ans.append("&amp;");
        } else {
            ans.append(str.charAt(ind));
        }
        return ans;
    }

    StringBuilder appPrefSuf(StringBuilder ans, String type, String str) {
        Map<String, String> to = Map.of("**", "strong", "__", "strong",
                "*", "em", "_", "em", "--", "s", "<<", "ins",
                "}}", "del", "p", "p", "`", "code");
        //System.err.println(type);
        ans.append("<" + to.get(type) + ">");
        if (type.equals("`")) {
            if (str.equals(">")) {
                ans.append("&gt;");
            } else if (str.equals("<")) {
                ans.append("&lt;");
            } else if (str.equals("&")) {
                ans.append("&amp;");
            } else {
                ans.append(str);
            }
        } else {
            ans.append(str);
        }
        return ans.append("</" + to.get(type) + ">");

    }

    char convertFromTo(char c) {
        if (c == '}') {
            return '{';
        }
        if (c == '<') {
            return '>';
        }
        return c;
    }

    void doForType2(String str, StringBuilder ans, int ind, char type) {
        //System.err.println(str+" " +ans+" "+" "+ ind+ type);
        ind += 2;
        int from = ind;
        while (ind + 1 < str.length() && (str.charAt(ind) != convertFromTo(type) || str.charAt(ind + 1) != convertFromTo(type))) {
            ind++;
            //System.err.println(str+" "+ind);
        }
        Parse m1 = new Parse();
        m1.parseBlock(str.substring(from, Integer.min(ind, str.length() - 1)));
        ind += 2;
        getResult = new Parse().appPrefSuf(ans, Character.toString(type) + Character.toString(type), m1.str);
        getInd = ind;
    }

    void doForType1(String str, StringBuilder ans, int ind, char type) {

        //System.err.println(str);
        /*
        if (ind+1 >=str.length()){
            ans = new Parse().appPrefSuf(ans, Character.toString(type), "");
            getResult = ans;
            getInd = ind;
            return;
        }

         */


        if (ind + 1 >= str.length() || !Character.isLetter(str.charAt(ind + 1))) {
            ans.append(str.charAt(ind));
            ind++;
            getResult = ans;
            getInd = ind;
            return;
        }
        ind++;
        int from = ind;
        while (ind < str.length() && str.charAt(ind) != type || str.charAt(ind + 1) == type || str.charAt(ind - 1) == type) {
            ind++;
            if (ind == str.length()) {
                ans.append(str.charAt(from - 1));
                ind = from;
                getResult = ans;
                getInd = ind;
                return;
            }
        }
        Parse m1 = new Parse();
        m1.parseBlock(str.substring(from, ind));
        ind++;
        ans = new Parse().appPrefSuf(ans, Character.toString(type), m1.str);
        getResult = ans;
        getInd = ind;
    }


    void parseBlock(String str) {
        //System.err.println(str);
        int ind = 0;
        StringBuilder ans = new StringBuilder();
        while (ind < str.length()) {
            Parse m1 = new Parse();
            if (ind + 1 < str.length() && str.charAt(ind) == '\\' && (str.charAt(ind + 1) == '*' ||
                    str.charAt(ind + 1) == '_' || str.charAt(ind + 1) == '\\' || str.charAt(ind + 1) == '>'
                    || str.charAt(ind + 1) == '<' || str.charAt(ind + 1) == '}' || str.charAt(ind + 1) == '{')) {
                ind++;
                if (ind < str.length() && str.charAt(ind) == '\\') {
                    ind++;
                }
                m1.getResult = new Parse().afterSlash(str, ans, ind);
                m1.getInd = ind + 1;
            } else if (ind + 1 < str.length() && str.charAt(ind) == '*' && str.charAt(ind + 1) == '*') {
                m1.doForType2(str, ans, ind, '*');
            } else if (str.charAt(ind) == '*') {
                m1.doForType1(str, ans, ind, '*');
            } else if (ind + 1 < str.length() && str.charAt(ind) == '_' && str.charAt(ind + 1) == '_') {
                m1.doForType2(str, ans, ind, '_');
            } else if (str.charAt(ind) == '_') {
                m1.doForType1(str, ans, ind, '_');
            } else if (ind + 1 < str.length() && str.charAt(ind) == '-' && str.charAt(ind + 1) == '-') {
                m1.doForType2(str, ans, ind, '-');
            } else if (ind + 1 < str.length() && str.charAt(ind) == '<' && str.charAt(ind + 1) == '<') {
                m1.doForType2(str, ans, ind, '<');
            } else if (ind + 1 < str.length() && str.charAt(ind) == '}' && str.charAt(ind + 1) == '}') {
                m1.doForType2(str, ans, ind, '}');
            } else if (ind < str.length() && str.charAt(ind) == '`') {
                ind++;
                int from = ind;
                while (ind < str.length() && str.charAt(ind) != '`') {
                    ind++;
                }
                m1.parseBlock(str.substring(from, ind));
                ind++;
                ans = appPrefSuf(ans, "`", m1.str);
                m1.getResult = ans;
                m1.getInd = ind;
            } else {
                if (ind != str.length() - 1 || str.charAt(ind) != '\n') {
                    ans = new Parse().afterSlash(str, ans, ind);
                }
                m1.getResult = ans;
                m1.getInd = ind + 1;
            }
            ans = m1.getResult;
            ind = m1.getInd;
        }
        this.str = ans.toString();
    }

    void parseNewBlock(String str) {
        //System.err.println(str);
        int ind = 0;
        int cntH = 0;
        while (ind < str.length() && str.charAt(ind) == '#') {
            cntH++;
            ind++;
        }
        StringBuilder ans = new StringBuilder();
        Parse m1 = new Parse();
        if (ind < str.length() && str.charAt(ind) == ' ' && cntH >= 1) {
            ans.append(String.format("<h%d>", cntH));
            m1.parseBlock(str.substring(ind + 1));
            ans.append(m1.str);
            //System.err.println(ans);

            ans.append(String.format("</h%d>", cntH));
        } else {
            m1.parseBlock(str);
            ans = appPrefSuf(ans, "p", m1.str);
        }
        this.str = ans.toString();

    }
}

public class Md2Html {

    public static void main(String[] args) {
        try {
            BufferedReader reader = new BufferedReader(new InputStreamReader(
                    new FileInputStream(args[0]), "utf-8"));
            String line;
            StringBuilder stack = new StringBuilder();
            Parse m1 = new Parse();
            Writer writer = new OutputStreamWriter(new FileOutputStream(args[1]), "utf-8");
            while ((line = reader.readLine()) != null) {
                if (!line.isEmpty()) {
                    stack.append(line + "\n");
                }
                while ((line = reader.readLine()) != null && !line.isEmpty()) {
                    stack.append(line + "\n");
                }

                if (!stack.isEmpty()) {
                    m1.parseNewBlock(stack.toString());
                    if (!m1.str.isEmpty()) {
                        writer.write(m1.str + System.lineSeparator());
                    }
                }
                stack = new StringBuilder();
            }
            writer.close();
            reader.close();
        } catch (IOException e) {
            System.err.println(e.getMessage());
        }

    }
}
//java -jar Md2HtmlInsDelTest.jar
//javac md2html/Md2html.java
