Proximal:
la 2x2: facem intre in si 2 cu stepul nostru
facem un for si in fucntie de  in ce cadran suntem facem functia (am folosit if pentru ca este
doar unu sau doi)
la resize: calculam factorii de scalare, facem matricea de transformare si transpusa ei. In for
calculam x_p si y_p si mergem  la cel mai apropiat pixel.
la rotate: facem sin si cos, matricea de transormare. In for calculam din nou x_p si y_p cu 
aceasta noua matrice si folosim functia de calculare a coef. In ea am calculat matricea A
cu formula, vectorul b cu ajutorul functiei, iar rezultatul este doar inv(A) * b.

Bicubic:
la resize: functiile sunt calculate cu functia. Derivatele sunt egale cu functiile, daca sunt primele
sau ultimele elemente sunt 0. Calculam iarasi matricea de transofrmare ca la resize, x_p si y_p si
calculam coef cu functia de coef bicubic. La functie avem matricea pe care o copiem. Ii calculam
transpusa si calculam matricea de rezultatele funciilor. Matricea coef este de forma L * matricea
noastra * Lt. La sfarsit doar folosim formula oentru a calcula R.

RGB la toate sunt efectiv fucntiile dar impartite (le impartim luand ori prima, a doua sau a treia din 
matricea tridimensionala).

