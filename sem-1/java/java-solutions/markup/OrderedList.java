package markup;

import java.util.List;

public class OrderedList extends AbstractMarkupList {
    public OrderedList(List<ListItem> args) {
        super(args);
    }

    @Override
    public void toHtml(StringBuilder str) {
        toHtml(str, "<ol>", "</ol>");
    }
}
