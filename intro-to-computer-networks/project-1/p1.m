clear;
clc;
close all;

T=8;
f = 1/T;
t = linspace(0, T, 1000);

bits = [0 1 1 0 0 0 1 0];
signal = zeros(size(t));

for k = 1:8
    signal(t >= (k-1) & t<k) = bits(k);
end

figure;
subplot(3,1,1);
hold on;
plot(t, signal, 'k', 'LineWidth', 2);
ylim([-0.2 1.2]);
title('Original Signal');
xlabel('Time');
ylabel('Amplitude');
grid on;


c = 3/4;
N_Values = 1:10;
colors = lines(length(N_Values));


subplot(3,1,2);
hold on;

for N = N_Values
    g = 0.5*c;
    for n = 1:N
        an = (1/(pi*n))*(cos((pi*n)/4)-cos((3*pi*n)/4)+cos((6*pi*n)/4)-cos((7*pi*n)/4));
        bn = (1/(pi*n))*(sin((3*pi*n)/4)-sin((pi*n)/4)+sin((7*pi*n)/4)-sin((6*pi*n)/4));
        
        g = g + an * sin(2*pi*N*f*t) + bn * cos(2*pi*n*f*t);


    end

    plot(t, g, 'Color', colors(N,:), 'DisplayName', sprintf('N = %d', N));
end

title('Fourier Series Approximation');
xlabel('Time');
ylabel('Amplitude');
legend show;
grid on;

a_vals = zeros(1,10);
b_vals = zeros(1,10);
rms_vals = zeros(1,10);

for n = 1:10
    a_vals(n) = (1/(pi*n))*(cos((pi*n)/4)-cos((3*pi*n)/4)+cos((6*pi*n)/4)-cos((7*pi*n)/4));
    b_vals(n) = (1/(pi*n))*(sin((3*pi*n)/4)-sin((pi*n)/4)+sin((7*pi*n)/4)-sin((6*pi*n)/4));
    rms_vals(n) = sqrt(a_vals(n)^2 + b_vals(n)^2);
end

subplot(3,1,3);
stem(1:10, rms_vals, 'filled', 'LineWidth', 1.5);
title('RMS Amplitude of Each Harmonic');
grid on;