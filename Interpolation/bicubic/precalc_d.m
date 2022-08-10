function [Ix, Iy, Ixy] = precalc_d(I)
    % =========================================================================
    % Prealculeaza matricile Ix, Iy si Ixy ce contin derivatele dx, dy, dxy ale 
    % imaginii I pentru fiecare pixel al acesteia.
    % =========================================================================
    
    % Obtinem dimensiunea imaginii.
    [m n nr_colors] = size(I);
    
    % TODO: Tranforma matricea I in double.
    I = double(I);

    % TODO: Calculeaza matricea cu derivate fata de x Ix.
    Ix = zeros(m, n);
    for i = 1 : m
        Ix(i, 1) = 0;
        Ix(i, n) = 0;
        for j = 2 : n - 1
            Ix(i, j) = fx(I, i, j);
        endfor
    endfor
    
    % TODO: Calculeaza matricea cu derivate fata de y Iy.
    Iy = zeros(m, n);
    for j = 1 : n
        Iy(1, j) = 0;
        Iy(m, j) = 0;
        for i = 2 : m - 1
            Iy(i, j) = fy(I, i, j);
        endfor
    endfor
    
    % TODO: Calculeaza matricea cu derivate fata de xy Ixy.
    Ixy = zeros(m, n);
    for i = 2 : m - 1
        for j = 2 : n - 1
            Ixy(i, j) = fxy(I, i, j);
        endfor
    endfor
    for j = 2 : n - 1    
        Ixy(1, j) = 0;
        Ixy(m, j) = 0;
    endfor
    for i = 2 : m - 1
        Ixy(i, 1) = 0;
        Ixy(i, n) = 0;
    endfor
    Ixy(1, 1) = 0;
    Ixy(1, n) = 0;
    Ixy(m, 1) = 0;
    Ixy(m, n) = 0;
   
    
endfunction

