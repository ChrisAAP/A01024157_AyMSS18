#include <string>
#include <iostream>
#include <list>

using namespace std;
class IVisitor;
class DocPart
{
public:
    string text;
    //virtual string toHTML() = 0;
    //virtual string toText() = 0;
    //virtual string toLatex() = 0;
    virtual void accept(IVisitor*) = 0;
};

class Text : public DocPart
{
public:
    void accept(IVisitor* visitor);
    /*
    string toHTML()
    {
        return text;
    }
    string toText()
    {
        return text;
    }
    string toLatex()
    {
        return text;
    }
    */
};

class Bold : public DocPart
{
public:
    void accept(IVisitor* visitor);
    /*
    string toHTML()
    {
        return "<b>" + text + "</b>";
    }
    string toText()
    {
        return text;
    }
    string toLatex()
    {
        return "\\textbf{" + text + "}";
    }
    */
};

class HyperLink : public DocPart
{
public:
    string URL;
    void accept(IVisitor* visitor);
    
    /*
    string toHTML()
    {
        return "<a href='" + URL + "'>" + text + "</a>";
    }
    string toText()
    {
        return text;
    }
    string toLatex()
    {
        return "\\href{" + URL + "}{" + text + "}";
    }
    */
};

class IVisitor
{
public:
    virtual void visit(HyperLink) = 0;
    virtual void visit(Text) = 0;
    virtual void visit (Bold) = 0;
};

class HTMLVisitor : public IVisitor
{
public:
    string out = "";
    void visit(HyperLink h)
    {
        
        out += "<a href='" + h.URL + "'>" + h.text + "</a>";
    } 
    void visit(Text h)
    {
        out += h.text;
    }
    void visit(Bold h)
    {
        out += "<b>" + h.text + "</b>";
    }
};

class TextVisitor : public IVisitor
{
public:
    string out = "";
    void visit(Text t)
    {
        out += t.text;
    }
    void visit(HyperLink t)
    {
        out += t.text;
    }
    void visit(Bold t)
    {
        out += t.text;
    }
};

class LatexVisitor : public IVisitor
{
public:
    string out = "";
    void visit(Text l)
    {
        out += l.text;
    }
    void visit(HyperLink l)
    {
        out += "\\href{" + l.URL + "}{" + l.text + "}";
    }
    void visit(Bold l)
    {
        out += "\\textbf{" + l.text + "}";
    }
    
};

void Bold::accept(IVisitor* visitor)
{
    visitor->visit(*this);
}

void Text::accept(IVisitor* visitor)
{
    visitor->visit(*this);
}
void HyperLink::accept(IVisitor* visitor)
{
    visitor->visit(*this);
}
class Document
{
public:
    list<DocPart*> docpart;
    void accept(IVisitor* visitor)
    {
        for(DocPart* d : docpart)
        {
            d->accept(visitor);
        }
    }
    /*
    string toHTML()
    {
        string out  = "";
        for(DocPart* d : docpart)
        {
            out += d->toHTML();
        }
        return out;
    }
    string toText()
    {
        string out2  = "";
        for(DocPart* d : docpart)
        {
            out2 += d->toText();
        }
        return out2;
    }
    string toLatex()
    {
        string out3  = "";
        for(DocPart* d : docpart)
        {
            out3 += d->toLatex();
        }
        return out3;
    }
    */
};


int main()
{
    
    Document d;
    Text t1;
    t1.text = "Hola, visita ";
    Bold t2;
    t2.text = "mi ";
    HyperLink t3;
    t3.URL = "www.mypage.com";
    t3.text = "pagina";

    d.docpart.push_back(&t1);
    d.docpart.push_back(&t2);
    d.docpart.push_back(&t3);
    /*
    cout << d.toHTML() << "\n";
    cout << d.toText() << "\n";
    cout << d.toLatex() << "\n";
    */
    HTMLVisitor* htmlvisitor = new HTMLVisitor;
    d.accept(htmlvisitor);
    cout << htmlvisitor->out;
}