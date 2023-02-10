package markup;

public class Text implements MarkupElements {
    private String str;

    public Text(String str) {
        this.str = str;
    }

    @Override
    public void toMarkdown(StringBuilder old) {
        old.append(str);
    }

    @Override
    public void toHtml(StringBuilder old) {
        old.append(str);
    }
}
