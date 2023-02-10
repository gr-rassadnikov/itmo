package markup;

import java.util.List;

public class Paragraph extends AbstractMarkupElement implements MarkupLists {

    public Paragraph(List<MarkupElements> args) {
        //System.err.printl("----")
        //toMarkdown(str, "", "");
        super(args);
    }

    public void toMarkdown(StringBuilder str) {
        toMarkdown(str, "", "");
    }

    @Override
    public void toHtml(StringBuilder str) {
        toHtml(str, "", "");
    }
}
