package markup;

import java.util.List;

public class Emphasis extends AbstractMarkupElement implements MarkupElements {
    public Emphasis(List<MarkupElements> args) {
        super(args);
    }

    @Override
    public void toMarkdown(StringBuilder str) {
        toMarkdown(str, "*", "*");
    }

    @Override
    public void toHtml(StringBuilder str) {
        toHtml(str, "<em>", "</em>");
    }
}
