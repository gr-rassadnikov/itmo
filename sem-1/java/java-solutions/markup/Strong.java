package markup;

import java.util.List;

public class Strong extends AbstractMarkupElement implements MarkupElements {
    public Strong(List<MarkupElements> args) {
        super(args);
    }

    @Override
    public void toMarkdown(StringBuilder str) {
        toMarkdown(str, "__", "__");
    }

    @Override
    public void toHtml(StringBuilder str) {
        toHtml(str, "<strong>", "</strong>");
    }
}
