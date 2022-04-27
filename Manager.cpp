/*Project-eket és rajtuk dolgozó Manager-eket szeretnénk kezelni. Alább látható a két típus definíciója.

Az elvárt működés, hogy a Project-ek máshol ne legyenek tárolva, csak a Manager-ek által. 
Egy Project-hez több Manager is csatlakozhat, majd bármikor elhagyhatják azokat.
Ha egy Project-et az utolsó Manager is elhagyott, akkor kerüljön törlésre!

Adja meg a Manager tagfüggvényeinek hiányzó definícióit!
*/
#include <iostream>
#include <string>
#include <map>
#include <memory>

using namespace std;

struct Project {
    int id;
    string name;

    Project(int id, const string& name)
    : id(id)
    , name(name)
    {
        cout << toString() << " has been started.\n";
    }
    ~Project() {
        cout << toString() << " has been abandoned.\n";
    }
    string toString() const {
        return "Project '" + name + "' (ID: " + to_string(id) + ")";
    }
};



class Manager {
    string name;
    map<int, shared_ptr<Project>> projects;

public:
    Manager(const string& name); // TODO

    string GetName() const { return name; }

    void StartProject(int id, const string& name); // TODO

    bool JoinProject(weak_ptr<Project> p); // TODO

    void AbandonProject(int id); // TODO

    weak_ptr<Project> GetProject(int id) const; // TODO
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Konstruktor, eltárolja a Manager nevét, inicializálja az adatstruktúrát
Manager::Manager(const string& name) : name(name) {                                         //PIPA
}

// Létrehoz egy egy új projektet a megadott ID-val és névvel, és eltárolja a Managerhez
// Feltételezhető, hogy minden projektnek egyedi ID-t adnak meg
void Manager::StartProject(int id, const string& name) {                                    //PIPA
    projects[id] = shared_ptr<Project> (new Project{id,name});                              //ez full
}

// Eltárolja, hogy a Manager részt vesz a megadott projektben
// Ha a projekt már megszűnt, adjon vissza hamis értéket, különben igazat
bool Manager::JoinProject(weak_ptr<Project> p){                                             //PIPA
    if(p.expired()){
        //ha megszűnt
        return false;
    }else{
        std::shared_ptr<Project> sp = p.lock();            
        projects[sp->id] = sp;
        return true;
    }

}

// Elhagyja a megadott ID-jú projektet, ami meg is szűnik, ha más már nem dolgozik rajta
// Ha a Manager nem dolgozik az adott ID-jú projekten, ne történjen semmi sem
void Manager::AbandonProject(int id) {                                                      //PIPA
    if ( projects.find(id) != projects.end() ) {
        //megtalálta és kitörli
        projects.erase(id);
    }
        //amugy meg nem csinál semmit
}

// Adjon vissza egy pointert a Manager adott ID-jú projektjére
// Ha az ID nem található, adjon vissza üres weak_ptr-t
weak_ptr<Project> Manager::GetProject(int id) const {                                       //PIPA
     if ( projects.find(id) != projects.end() ) {
        //megtalálta és visszaadja
        return projects.find(id)->second;
    } else {
        return weak_ptr<Project>{};
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(){
    Manager a("Romeo Alpha");
    Manager b("Julia Beta");

    cout << a.GetName() << " starts then abandons project 42.\n";
    a.StartProject(42, "EV motor design");
    auto p42 = a.GetProject(42);
    a.AbandonProject(42);
    cout << "Try to get abandoned project.\n";
    auto err = a.GetProject(42);
    cout << "Try to join abandoned project.\n";
    b.JoinProject(err);
    cout << "Try to get unknown project.\n";
    err = b.GetProject(404);
    cout << "Try to join unknown project.\n";
    a.JoinProject(err);

    bool ok = a.JoinProject(p42);
    if (ok) cout << "Error: joined an abandoned project.\n";
    ok = b.JoinProject(p42);
    if (ok) cout << "Error: joined an abandoned project.\n";

    cout << a.GetName() << " starts project 55.\n";
    a.StartProject(55, "Self-driving vehicle");                      
    auto p55 = a.GetProject(55);
    ok = b.JoinProject(p55);
    if (!ok) cout << "Error: could not join project.\n";
    a.AbandonProject(55);
    cout << b.GetName() << " took over project 55.\n";

    b.StartProject(23, "Fix brake system");
    ok = a.JoinProject(b.GetProject(23));
    if (!ok) cout << "Error: could not join project.\n";
    a.AbandonProject(23);
    cout << a.GetName() << " briefly joined project 23.\n";
    cout << b.GetName() << " finished project 23.\n";
    b.AbandonProject(23);

    b.StartProject(7, "External supply");
    Manager* e = new Manager("Eszter Nale");
    e->JoinProject(b.GetProject(7));
    b.AbandonProject(7);
    cout << e->GetName() << " leaves.\n";
    delete e;

    cout << a.GetName() << " rejoins project 55.\n";
    ok = a.JoinProject(p55);
    if (!ok) cout << "Error: could not join project.\n";
/*
*/
    return 0;
}

/* RESULT
Romeo Alpha starts then abandons project 42.
Project 'EV motor design' (ID: 42) has been started.
Project 'EV motor design' (ID: 42) has been abandoned.
Try to get abandoned project.
Try to join abandoned project.
Try to get unknown project.
Try to join unknown project.
Romeo Alpha starts project 55.
Project 'Self-driving vehicle' (ID: 55) has been started.
Julia Beta took over project 55.
Project 'Fix brake system' (ID: 23) has been started.
Romeo Alpha briefly joined project 23.
Julia Beta finished project 23.
Project 'Fix brake system' (ID: 23) has been abandoned.
Project 'External supply' (ID: 7) has been started.
Eszter Nale leaves.
Project 'External supply' (ID: 7) has been abandoned.
Romeo Alpha rejoins project 55.
Project 'Self-driving vehicle' (ID: 55) has been abandoned.
*/