%trajC 
%
%   -Cálculo de los puntos de una trayectoria cartesiana
%
%   Ejemplo: [trj]=trajC(A,B,n)
%   
%   A = [1 2 3] : son las coordenadas del primer punto
%   B = [4 5 6] : son las coordenadas del segundo punto
%   n = 10      : son el numero de puntos que constituyen la trayectoria
%
%   trj = es el conjuntos de puntos desde A hasta B en línea recta
%

function [trj]=trajC(A,B,n)

cuenta=0;
paso=1/n;
for i=0:paso:1
    cuenta=cuenta+1;
    trj(cuenta,:)=A+(B-A)*i;
end