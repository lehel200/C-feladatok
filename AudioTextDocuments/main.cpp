/*
Implementálja a válaszdobozban megjelenő kódban a hiányzó részeket ahhoz, hogy a program leforduljon és az alábbi elvárt kimenetet adja:

mp3 file entitled: Back Chat - with size of 3.41Mb
flac file entitled: All you need is love - with size of 5.89Mb
Text document entitled: Nobel.txt - with size of 2.2Mb
af3: cannot create based on arguments
mp3 file entitled: Back Chat - with size of 3.41Mb
Text document entitled: Nobel.txt - with size of 2.2Mb
*/

#include <iostream>
#include <string>
#include <vector>
#include <variant>

using sdvar = std::variant<std::string, double>; // ezek utan sdvar tipus is hasznalhato

class Document {
    const std::string name;
    double sizeInMbs;
public:
    Document(std::string nm, double sz) : name{ nm }, sizeInMbs{ sz } {}
    virtual ~Document() {};
    const std::string& getName() { return name; }
    double getSize() { return sizeInMbs; }
    virtual void printDetails() = 0;
};

class TextDocument : public Document {
public:
    TextDocument(std::string nm, double sz) : Document(nm,sz) {}        // a konstruktort valositsa meg!
    
    void printDetails() override {
        std::cout << "Text document entitled: " << getName() << " - with size of " << getSize() << "Mb" << std::endl;
    }
};

class AudioFile : public Document {
    const std::string format;
public:
    AudioFile(std::string nm, double sz, std::string f) : Document(nm, sz), format(f) {}    // a konstruktort valositsa meg!
    
    void printDetails() override {
        std::cout << format << " file entitled: " << getName() << " - with size of " << getSize() << "Mb" << std::endl;
    }
};

class DocumentFactory {
private:
    DocumentFactory() {}
public:
    ///////////////////////////////////////
    static Document* NewDocument(std::string type,const std::vector<sdvar>& v) {
        if (type == "text")
        {
            std::string nm;
            double sz{};

            nm = *std::get_if<std::string>(&v[0]);
            sz = *std::get_if<double>(&v[1]);

            return new TextDocument(nm, sz);
        }
        else if (type == "music") 
        {
            if (v.size() == 3)
            {
                std::string nm;
                std::string frmt;
                double sz{};

                nm = *std::get_if<std::string>(&v[0]);
                frmt = *std::get_if<std::string>(&v[1]);
                sz = *std::get_if<double>(&v[2]);
                
                return new AudioFile(nm, sz, frmt);
            }
            else 
            {
                return nullptr;
            }
        }
        else { throw 0; }
    }
    // implementalja NewDocument() metódust ugy hogy a pelda kod lefusson
    // az elso argumentum string, ertek ami lehet "text" vagy "music", es ettol fugg a letrejovo document tipusa
    // a masodik argumentum a konstruktornak tovabbitando sdvar ertekeket tartalmazo vector
};



int main() 
{
	Document* af1 = DocumentFactory::NewDocument("music", { sdvar("Back Chat"), sdvar("mp3"), sdvar(3.41) }); // a variant vektort az initializer-list hozza letre!
	Document* af2 = DocumentFactory::NewDocument("music", { sdvar("All you need is love"), sdvar("flac"), sdvar(5.89) });
	Document* tf1 = DocumentFactory::NewDocument("text", { sdvar("Nobel.txt"), sdvar(2.20) });
    Document* af3 = DocumentFactory::NewDocument("music", { sdvar("Some audio"), sdvar(5.00) }); // nincs eleg argumentum!
	if (af1) { af1->printDetails(); }
	else { std::cout << "af1: cannot create based on arguments" << std::endl; }
	if (af2) { af2->printDetails(); }
	else { std::cout << "af2: cannot create based on arguments" << std::endl; }
    if (tf1) { tf1->printDetails(); }
	else { std::cout << "tf1: cannot create based on arguments" << std::endl; }
	if (af3) { af3->printDetails(); }
	else { std::cout << "af3: cannot create based on arguments" << std::endl; }
	dynamic_cast<AudioFile*>(af1)->printDetails();
    dynamic_cast<TextDocument*>(tf1)->printDetails();

	delete af1;
	delete af2;
	delete tf1;
};
