package markup;

import java.util.List;

public class UnorderedList extends AbstractMarkupList {
    public UnorderedList(List<ListItem> args) {
        super(args);
    }

    @Override
    public void toHtml(StringBuilder str) {
        toHtml(str, "<ul>", "</ul>");
    }
}
