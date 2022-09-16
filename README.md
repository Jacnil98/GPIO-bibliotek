# Projekt I Hårdvarunära programmering - Ela21

#### Utfört av: Jacob Nilsson & Jacob Lundkvist
#### Handledare: Erik Pihl
*****
  
### Introduktion
Detta skolprojekt gick ut på att konstruera ett GPIO-biblotek mot en Raspbery Pi 4 med hjälp av Linux interface libgpiod. Biblioteket skulle sedan verifieras i en exempelkod som i detta fall skulle utnyttja pthread. 

Bibloteket funktionallitet ska innehålla enkel styrning för in- och utenheter.   
****
### Output devices  
Ska kunnas sättas på, stängas av samt blinka med önskad fördröjning.  
Kan även läsas av.

### Input devices 
Ska kunnas bestämma om det ska vara aktivt höga eller aktivt låga. Sedan så ska även flankdektekteringen för stigande flank, fallande flank eller båda flanker.

***

### Bibliotekets funktioner
bool read() - reads value GPIO instance.  
void blink(const uint16_t blink_speed) - toggles output device on/off in a series.  
void on()  - sets value high/1.  
void off() - sets value low/0.  
void toggle()   - toggles output value.

****

### Resultat
Resultatet blev som förväntat. Biblioteket fick den funktionalitet som efterfrågades samt att den fungerar utan några problem i den exempelkoden som sattes ihop. Ett val var att lägga till ett user-interface i terminalen så att inga knappar behövs användas för att växla mellan olika lägen på utportarna. Detta bibliotek skapades i syftet för att användas i framtida projekt och kommer komma väl till hands för enkelt styrning av in & utenheter.
****

### Diskussion
Vi upplevde att steget mellan godkänt och väl godkänt var stort och för oss personligen såg vi inte hur vi skulle kunna klara VG-delen själva. Däremot gjorde vi en kompromiss där vi istället för att ge oss på alla punkter för VG-nivån, valde att göra ett interface där man enkelt kunde styra utenheterna från terminalen utöver de två tryckknapparna som fanns kopplade.  
  
En del vi hade kunnat göra annorlunda hade varit att använda oss av c++ wrappern av gpiod.h som heter gpiod.hpp men projektet blev väldigt lyckat trots det. 

Det var kul att göra vårat första riktiga projekt i C++ och önskar att utbildningen skulle satsat mer på C++ i tidigare utbildningen. Då vi har haft väldigt mycket fokus på C och känt att inget företag vi hört talas om söker en C-programmerare utan brukar oftast vara C++ eller Python.  
  

****