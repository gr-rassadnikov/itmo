package markup;

import java.util.List;

public class Strikeout extends AbstractMarkupElement implements MarkupElements {
    public Strikeout(List<MarkupElements> args) {
        super(args);
    }

    @Override
    public void toMarkdown(StringBuilder args) {
        toMarkdown(args, "~", "~");
    }

    @Override
    public void toHtml(StringBuilder str) {
        toHtml(str, "<s>", "</s>");
    }
}
