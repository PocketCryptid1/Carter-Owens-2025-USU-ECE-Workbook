clear; close all; clc;

c = 3e8;                
Pt_dbm = 30;            
Gt = 3;                 
Gr = 1;                 
L_tx = 1;               
L_rx = 2;              
N0_dbmHz = -174;        
B = 2e6;       

% 2a
f_24 = 2.4e9;
d_list = [100, 200, 300, 500];

fspl = @(d,f) 20*log10(4*pi.*d.*f./c);

FSPL_d = fspl(d_list, f_24);

figure;
semilogx(d_list, FSPL_d, '-o','LineWidth',1.4);
grid on;
xlabel('Distance d (m)'); ylabel('FSPL (dB)');
title('FSPL vs distance at f = 2.4 GHz');
xticks(d_list);

d_fixed = 200;
f_list = [1e9, 2.4e9, 6e9, 8e9];
FSPL_f = fspl(d_fixed, f_list);

figure;
plot(f_list/1e9, FSPL_f, '-s','LineWidth',1.4);
grid on;
xlabel('Frequency (GHz)'); ylabel('FSPL (dB)');
title('FSPL vs frequency at d = 200 m');
xticks(f_list/1e9);

% 2b
recv_power_dbm = @(d,f) Pt_dbm + Gt - L_tx - fspl(d,f) + Gr - L_rx;

N_dbm = N0_dbmHz + 10*log10(B);

% i)
Pr_i = arrayfun(@(f) recv_power_dbm(d_fixed,f), f_list);
SNR_db_i = Pr_i - N_dbm;
SNR_lin_i = 10.^(SNR_db_i/10);
Capacity_i = B .* log2(1 + SNR_lin_i);

% ii)
Pr_ii = arrayfun(@(d) recv_power_dbm(d,f_24), d_list);
SNR_db_ii = Pr_ii - N_dbm;
SNR_lin_ii = 10.^(SNR_db_ii/10);
Capacity_ii = B .* log2(1 + SNR_lin_ii);

fprintf('\nCase (i)\n');
for i=1:length(f_list)
    fprintf(' f=%.1f GHz: Pr = %.3f dBm, SNR = %.3f dB, Capacity = %.3f Mbps\n', ...
        f_list(i)/1e9, Pr_i(i), SNR_db_i(i), Capacity_i(i)/1e6);
end

fprintf('\nCase (ii)\n');
for i=1:length(d_list)
    fprintf(' d=%d m: Pr = %.3f dBm, SNR = %.3f dB, Capacity = %.3f Mbps\n', ...
        d_list(i), Pr_ii(i), SNR_db_ii(i), Capacity_ii(i)/1e6);
end

figure;
plot(f_list/1e9, Capacity_i/1e6, '-o','LineWidth',1.4);
grid on;
xlabel('Frequency (GHz)'); ylabel('Capacity (Mbps)');
title('Capacity vs Frequency (d = 200 m)');
xticks(f_list/1e9);

figure;
plot(d_list, Capacity_ii/1e6, '-o','LineWidth',1.4);
grid on;
xlabel('Distance (m)'); ylabel('Capacity (Mbps)');
title('Capacity vs Distance (f = 2.4 GHz)');
xticks(d_list);
