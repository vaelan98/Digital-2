% Laboratorio 12
%Juan Gonzalez 17594
%Sección 10


sonido = audiorecorder(44100,16,1);
recordblocking(sonido,1);
play(sonido);


%parte1.1
x= sonido.getaudiodata;
%%
%parte1.2
soundsc(x, 44100,16);

%se escucha similar que al utilizar play
%%
% parte 1.3 y parte 1.5
y = zeros(size(x));
for n= 1:length(x)
    if n < 20001
        y(n)=x(n);
    end
    if n>=20001
        y(n) = x(n) + x(n-20000);
    end
end
 
%%
%parte 1.4

%hay una frecuencia de muestreo de 44100Hz ya ue hay 44100 datos que se
%usan en 1 segundo.

%por lo tanto el delay es
delay= 20000/length(x)*1000;

%%
%parte 1.6
soundsc(y,44100,16);
% se oye eco del hola 

%%
%parte 1.7
%variables 
Fs = 44100;                         
Ts = 1/Fs;       
N = length(x);        
t = (0:(N-1))*Ts; 
figure(1);clf;
subplot(2,1,1);
plot(t,x);
title(' x vs tiempo');
xlabel('tiempo');
ylabel('x');
subplot(2,1,2);
plot(t,y);
title(' y vs tiempo');
xlabel('tiempo');
ylabel('y');

%parte 1.8 

alfa=0.5;
D2= Fs*0.25;
y2= zeros(size(x));
%parte 1.9
for n = 1:length(x)
    if n<D2+1
        y2(n) = x(n);
    end
    if n>= D2+1
        y2(n)= x(n) +(1-alfa)*x(n-D2) + alfa*y2(n-D2);
    end
end
%%
%parte 1.10
soundsc(y2,44100,16);
% la voz se repite como 3 vceces y en segundo como el tercero , se sienten
% como eco que van decrementando con el tiempo
%%
%parte 1. 11

figure(2);clf;
subplot(2,1,1);
plot(t,x);
title(' x vs tiempo');
xlabel('tiempo');
ylabel('x');
subplot(2,1,2);
plot(t,y2);
title(' y2 vs tiempo');
xlabel('tiempo');
ylabel('y2');
%%
%

%datos workspace
%parte 2.1,2.2, 2.3
t_sim=1;
datos = zeros(length(x),2);
datos(:,1) = t;
datos(:,2) = x;
%inciso 3
%datos que salen de simulink
%mi simulink 2017 me tira de un solo los valores
y3=saldatos;
t3=tout;
%%
%parte 4
soundsc(y3,Fs);
%suena igual que en el ejemplo 10
%%
% parte 5
figure(3);clf;
subplot(2,1,1);
plot(t,x);
title(' x vs tiempo');
xlabel('tiempo');
ylabel('x');
subplot(2,1,2);
plot(t3,y3);
title(' y3 vs tiempo');
xlabel('tiempo');
ylabel('y3');

%%
%parte 6
y4=saldatos;
t4=tout;
soundsc(y4,Fs);
% al principio se parace al ejercicio anterior pero con la diferencia que
% entre mas pasa el tiempo mas se dispersa la voz.

%%

%parte7
%con alfa=0.8
y5=saldatos;
t5=tout;
soundsc(y5,Fs);
%se escucha igual que el anterior pero con el audio mas debil 

%%
%parte 8
%alfa=0.2
y6=saldatos;
t6=tout;
soundsc(y6,Fs);

%el audio decremneta bastante se sienten mas ecos pero solo diciendo la
%ultima frase y cada vez baja el tono mas y maz hasta que es casi nulo.
%%
%parte9
figure(4);clf;
subplot(3,1,1);
plot(t4,y4);
title(' y4 vs tiempo');
xlabel('tiempo');
ylabel('y4');
subplot(3,1,2);
plot(t5,y5);
title(' y5 vs tiempo');
xlabel('tiempo');
ylabel('y5');
subplot(3,1,3);
plot(t6,y6);
title(' y6 vs tiempo');
xlabel('tiempo');
ylabel('y6');

%% 

%variables
save('variableslab12','x','t','y','y2','t3','y3','t4','y4','t5','y5','t6','y6');




