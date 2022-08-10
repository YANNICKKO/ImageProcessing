function A = bicubic_coef(f, Ix, Iy, Ixy, x1, y1, x2, y2)
    % =========================================================================
    % Calculeaz? coeficien?ii de Interpolare Bicubic? pentru 4 puncte al?turate
    % =========================================================================

    % TODO: Calculeaz? matricile intermediare.
    L = [1 0 0 0; 0 0 1 0; -3 3 -2 -1; 2 -2 1 1];
    Lt = L';
    % TODO: Converte?te matricile intermediare la double.
    L = double(L);
    Lt = double(Lt);
    % TODO: Calculeaz? matricea final?.
    c1 = [f(y1,x1); f(y1,x2); Ix(y1,x1); Ix(y1,x2)];
    c2 = [f(y2,x1); f(y2,x2); Ix(y2,x1); Ix(y2,x2)];
    c3 = [Iy(y1,x1); Iy(y1,x2); Ixy(y1,x1); Ixy(y1,x2)];
    c4 = [Iy(y2,x1); Iy(y2,x2); Ixy(y2,x1); Ixy(y2,x2)];
    A = L * [c1 c2 c3 c4] * Lt;
endfunction