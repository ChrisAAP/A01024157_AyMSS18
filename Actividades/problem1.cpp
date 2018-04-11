#include <string>
#include <iostream>
#include <list>

using namespace std;

class DocPart
{
public:
    string text;
    virtual string toHTML() = 0;
    virtual string toText() = 0;
    virtual string toLatex() = 0;
};

class Text : public DocPart
{
public:
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
};

class Bold : public DocPart
{
public:
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

};

class HyperLink : public DocPart
{
public:
    string URL;
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
};

class Document
{
public:
    list<DocPart*> docpart;
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

    cout << d.toHTML() << "\n";
    cout << d.toText() << "\n";
    cout << d.toLatex() << "\n";
    
}