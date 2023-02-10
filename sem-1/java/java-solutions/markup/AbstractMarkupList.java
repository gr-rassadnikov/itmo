package markup;

import java.util.List;

public abstract class AbstractMarkupList implements MarkupLists {
    private List<ListItem> args;

    AbstractMarkupList(List<ListItem> args) {
        this.args = args;
    }

    public void toHtml(StringBuilder str, String front, String back) {
        str.append(front);
        for (ListItem i : args) {
            i.toHtml(str);
        }
        str.append(back);
    }
}
