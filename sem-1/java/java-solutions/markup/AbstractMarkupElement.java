package markup;

import java.util.List;

public abstract class AbstractMarkupElement {
    private List<MarkupElements> args;

    AbstractMarkupElement(List<MarkupElements> args) {
        this.args = args;
    }

    protected void toMarkdown(StringBuilder str, String front, String back) {
        str.append(front);
        for (MarkupElements i : args) {
            i.toMarkdown(str);
        }
        str.append(back);
    }

    protected void toHtml(StringBuilder str, String front, String back) {
        str.append(front);
        for (MarkupElements i : args) {
            i.toHtml(str);
        }
        str.append(back);
    }
}
