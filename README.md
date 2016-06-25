A feladat egy üzenet átjuttatása egy zajos csatornán, ahol random zaj rakódik rá, majd a fogadó oldalon az üzenet visszaállítása és a lehetőség szerinti legjobb zajmentesítése.
Kódoló oldal:
A kódoló oldalon a felhasználó begépel vagy szöveges fájlból  bevisz egy angol üzenetet.
A rendszer a szöveget átalakítja a karaktereknek megfelelő ascii kódokká (számokká), majd egy NxN-es mátrixba rendezi az üzenetet, a hiányzó részeket egy lefoglalt karakterrel kipótolva. Ezt azért, hogy a matematikai műveletek értelmezve legyenek az elemeken.
A mátrixon mátrix transzformációkat hajt végre a rendszer. Például megszorozza kettővel, majd hozzáad egy tetszőleges mátrixot.
Ez az üzenet megy át a csatornán, ahol random módon zaj rakódik rá (egyes karakterek elvesznek, felcserélődnek). Az elveszett karaktereket minden esetben ‘#’ karakterré cseréli a csatorna.
Készítsetek egy függvényt, ami a csatorna tulajdonságait szimulálja. Paraméterben lehessen megadni, az üzenetet, amit átküldünk a csatornán.

Továbbá:  
egy double értékként, hogy a karakterek hányadát befolyásolja a csatorna, majd ennek függvényében változtassa meg őket. (pl.: ha 0,5 akkor a karakterek felét módosítja), azaz random módon felcserél karaktereket vagy #-ká cserél.
 
Az így kapott eredményt az ascii karakterek szerint vissza alakítja a rendszer majd huffman kódolja. Azaz tömöríti az üzenetet.
Ezután dekódlja, majd az üzenetet prediktálja a program.
 
Dekódoló oldal:
A  bejövő üzenetet huffman dekódolja a rendszer
A transzformációk inverzét elvégezve előállítjuk az eredeti szöveget
Prediktálás:
Szótár alapon, a rendszer próbálja kitalálni mi volt az eredeti üzenet, miután átment a csatornán. Az előre adott szöveg bázis feldolgozása után építsen szótárat, majd a hiányzó karaktereket próbálja megtippelni.
Elvárt transzformációk:
Mátrix összeadás, kivonás, szorzás, skalárral való összeadás, kivonás, szorzás, osztás, transzponált számítás.
A titkosításnál legalább három egymás utáni transzformációt alkalmazni kell. Vigyázzunk, hogy ez olyan legyen, melynek az inverze számolható!
