package markup;

import java.util.List;

public class ListItem {
    private List<MarkupLists> args;

    public ListItem(List<MarkupLists> args) {
        this.args = args;
    }

    public void toHtml(StringBuilder str) {
        str.append("<li>");
        for (MarkupLists i : args) {
            i.toHtml(str);
        }
        str.append("</li>");
    }

}
