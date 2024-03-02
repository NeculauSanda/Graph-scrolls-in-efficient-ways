# Graph-scrolls-in-efficient-ways

    1.Descriere
    
Ne aflăm în anul 1783 în Bristol și Jim Hawkins intră în posesia unei hărți vechi a orașului și a unui mesaj ce conține indicații menite să-l conducă la o insulă plină de comori. Pe hartă sunt marcate cele mai importante obiective de la acea vreme din oraș. Mesajul care însoțește harta ne spune că "Orașul Bristol este unul dintre cele mai vechi orașe din Regatul Unit, cu o istorie bogată şi îndelungată. Oraşul a început să se dezvolte într-un mod organizat în jurul secolului al XI-lea. În acea perioadă, Bristol-ul era un important centru comercial datorită poziției sale strategice de-a lungul râului Avon. Astfel era și un loc frecventat de pirați. Transportul mar- itim era principala modalitate de a aduce mărfuri în oraș și locuitorii, în special proprietarii de magazine și ateliere, au fost constrânși să găsească rută cât mai convenabilă pe care să transporte marfa. Ruta trebuia să conțină toate punctele specificate pe harta și să fie minimă. Pentru a găsi următorul indiciu care ne va conduce la comoară, trebuie să găsim ruta de trans- port folosită în acea perioadă și costul ei. În cazul în care nu putem ajunge la toate obiectivele pe uscat, va trebui să stabilim câte o rută principală și costul ei minim pentru fiecare grup în parte."

    2. Cerinţă 1
    
Pentru această cerință, harta este reprezentată sub forma unui graf neorientat. Obiectivele din oraș reprezintă nodurile grafului, iar muchiile sunt echivalentul unor drumuri bidirecționale care există între aceste noduri. Pentru fiecare drum cunoaştem o distanță. Există însă situații în care harta este împărțită în mai multe zone care sunt despărțite de ape.


Voi va trebui să-l ajutați pe Jim Hawkins să determine pentru o hartă dată numărul de zone care sunt despărțite de ape.

După ce determinați numărul de zone, va trebui ca pentru fiecare zonă să îl ajutați pe Jim Hawkins să determine ce drumuri ar trebui să renoveze astfel încât costul total al acestora să fie minim și indiferent de ce obiectiv alegem să putem ajunge în oricare altul aflat pe aceeași bucată de uscat cu el parcurgând doar drumuri renovate.


Va trebui să afișați costul total al drumurilor ce urmează să fie renovate pentru fiecare zona despărţită de ape în ordine crescătoare.
Astfel, pentru cerința 1 veți avea de rezolvat două sarcini:

a) Determinarea numărului de zone care sunt despărțite de ape.

b) Pentru fiecare zonă despărțită de ape, trebuie să determinați costul total minim al dru- murilor ce ar trebui să fie renovate.

    2.1 Formatul fişierelor
    
Fişierul de intrare

• Pe prima linie din fișierul de intrare vor exista două numere N și M, iar N reprezintă numărul de obiective aflate pe hartă și M reprezintă numărul de drumuri bidirecționale care există între aceste obiective.

• Pe următoarele M linii vom avea descrise drumurile bidirecționale. Fiecare astfel de linie va conţine două şiruri de caractere și un număr natural (cost), despărțite printr-un spațiu. Spre exemplu:

Ferma Brutaria 1

Numele fişierului din care se citesc datele este "tema3.in".

    Observaţie
    
Numele obiectivelor din oraș va fi format dintr-un singur cuvânt.

Fişierul de ieșire

• Pe prima linie se va scrie un număr natural K reprezentând numărul de zone care sunt despărțite de ape.

• Pe următoarele K linii, vom scrie câte un număr natural cost_total[i] ce reprezintă costul total al drumurilor ce trebuie să fie renovate pentru zona i.
    
    Observație
Aceste valori sunt afisate în ordine crescătoare!



    3. Cerinţă 2
    
Harta găsită ne conduce la insulă. Ajunși aici, trebuie să ancorăm nava la o distanţă destul de mare de mal, pentru că adâncimea apei este prea mică în unele locuri. Astfel, echipajul nostru este nevoit să folosească o barcă pentru a căra comoara la corabie. Harta ne indică zonele prin care putem trece fără să declanșăm capcanele din jurul insulei. Sensul de trecere între două zone de pe hartă este specificat. Comoara este de mult timp ascunsă pe insulă, și între timp s-au format dune de nisip pe traseele indicate pe hartă. Înainte să înceapă încărcarea comorii pe corabie, echipajul analizează cu atenție drumul de la insula comorii la navă și marchează dunele de nisip. Fiecare nod are o valoare care reprezintă adâncimea apei în punctul respectiv. Cu cât încărcăm mai mult barca, cu atât se scufundă mai mult și nu va mai putea trece prin anumite zone. Pentru că timpul este prețios, iar echipajul este deja extenuat, trebuie să găsim cea mai bună variantă de a transporta comoara. Un membru al echipajului a venit cu o idee. Pe hartă, arcele reprezintă distanţa dintre două puncte prin care putem trece, iar nodurile au atașate o valoare pentru adâncime. Membrul echipajului a determinat o formulă care să atribuie un scor unui arc pe baza distanței și a adâncimii. Folosim acest scor pentru a evalua fiecare alegere și, în final, să determinăm cea mai bună rută de urmat pentru a duce comoara de pe insulă la corabie. Odată aleasă ruta, aceasta nu poate fi schimbată. În mod ideal, căutăm rute cât mai scurte, pe care să putem căra cât mai mult din comoară. Formula folosită pentru evaluarea unui arc este:

    Observație
scor(arc) = distanță (arc)/ adâncime (nodul_catre_care_se _se_duce_arcul)

Tipul variabilei folosit pentru calculul scorului este float.

    Important
Pentru rezolvarea acestei cerințe, vom porni de la Algoritmul lui Dijkstra.



    3.1 Formatul fişierelor
    
    Fişierul de intrare

• Pe prima linie din fișierul de intrare găsim două numere N și M. N reprezintă numărul de puncte aflate pe hartă care ne indică zonele prin care putem trece fără să declanşăm capcanele din jurul insulei. M reprezintă numărul de drumuri unidirecționale care există între aceste puncte.

• Pe următoarele M linii vom avea descrise drumurile unidirecționale. Fiecare astfel de linie va conţine două șiruri de caractere și un număr natural (distanța), despărțite printr-un spațiu. Spre exemplu:

Insula Nod 2 5

• Pe următoarele N linii se citesc perechi formate din numele punctului de pe hartă urmat de adâncimea apei în punctul respectiv (număr natural).

• Pe ultima linie se citește o valoare care reprezintă greutatea comorii în kg (număr natural).

• În cazul nodurilor Insulă și Corabie adâncimea nu este folosită, aceasta o sa fie considerată o valoare implicită 1.

    Fişierul de ieşire

Toate datele afișate sunt numere naturale.

• Pe prima linie se vor scrie toate nodurile care constituie cel mai bun drum pentru a căra comoara de la insulă la corabie.

• Pe a doua linie se va afișa costul total al drumului.

• Pe a treia linie se va afișa greutatea maximă pe care o poate avea barca pentru a trece pe traseul găsit.

• Pe ultima linie se va afișa numărul de drumuri făcute pentru a căra întreaga comoară. • De asemenea, trebuie să ne asigurăm că există cel puțin o rută prin care putem ajunge de la Corabie la Insulă, altfel vom afișa mesajul "Echipajul nu poate ajunge la insula" și problema s-a încheiat (nu putem încerca să găsim o rută de la Insulă la Corabie dacă nu putem ajunge la insulă în primul rând).

• Dacă găsim o rută de la Corabie la Insulă, însă nu există nicio rută de la Insulă la Corabie, se va afișa mesajul "Echipajul nu poate transporta comoara înapoi la corabie".
