#include "iostream"
using namespace std;

#include "tinyxml/tinyxml.h"

int main(){
    TiXmlDocument doc;
    if(!doc.LoadFile("eenCD.xml")) {
        std::cerr << doc.ErrorDesc() << std::endl;
        return 1;
    }

    TiXmlElement* root = doc.FirstChildElement();
    if(root == NULL) {
        std::cerr << "Failed to load file: No root element." << std::endl;
        doc.Clear();
        return 1;
    }

    for(TiXmlElement* elem = root->FirstChildElement(); elem != NULL;
        elem = elem->NextSiblingElement()) {
        string elemName = elem->Value();

        for(TiXmlNode* e = elem->FirstChild(); e != NULL; e = e->NextSibling()){
            TiXmlText* text = e->ToText();

            if(text == NULL)
                continue;
            string t = text->Value();

            if(elemName == "TITLE") {
                cout << t << endl;
            }
            else if(elemName == "ARTIST") {
                cout << t << endl;
            }

        }
    }

    doc.Clear();
}