function out = proximal_2x2(f, STEP = 0.1)
    % ===================================================================================
    % Aplica Interpolare Proximala pe imaginea 2 x 2 f cu puncte intermediare echidistante.
    % f are valori cunoscute în punctele (1, 1), (1, 2), (2, 1) ?i (2, 2).
    % Parametrii:
    % - f = imaginea ce se va interpola;
    % - STEP = distan?a dintre dou? puncte succesive.
    % ===================================================================================
    
    % TODO: Defineste coordonatele x si y ale punctelor intermediare.
    x_int = 1 : STEP : 2;
    y_int = 1 : STEP : 2;


    % Se afl? num?rul de puncte.
    n = length(x_int);

    % TODO: Cele 4 puncte încadratoare vor fi aceleasi pentru toate punctele din interior.

    %Avand in vedere ca putem avea x, y 1 sau 2 putem 
    %pune 1 si adunam cu un 0 sau 1 daca i > jumatata sau j
    %deci nu folosim x1/x2 si y1/y2
    x1 = y1 = 1;
    x2 = y2 = 2;

    % TODO: Initializeaza rezultatul cu o matrice nula n x n.
    out = zeros(n,n);
    % Se parcurge fiecare pixel din imaginea finala.
    for i = 1 : n
        for j = 1 : n
            % TODO: Afla cel mai apropiat pixel din imaginea initiala.
            out(i, j) = f((i > n/2) + 1, (j > n/2) + 1);
            % TODO: Calculeaza pixelul din imaginea finala.
    
        endfor
    endfor

endfunction

