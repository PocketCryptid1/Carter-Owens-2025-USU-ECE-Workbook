# Homework 6

## 1

A is higher
A: 800 kbps
B: 200 kbps

## 2

UDP provides port mux and demux

## 3

Process IDs are not predictable, they change and are reused
with port numbers, a single process can handle multiple connections

## 4

40 ms

## 5

16 KB

## 6

66 KB

## 7

### 7.1

EstimatedRTT: 100.75 ms

DevRTT: 5.06 ms

TimeoutInterval: 121.00 ms

### 7.2

EstimatedRTT: 103.16 ms

DevRTT: 8.01 ms

TimeoutInterval: 135.19 ms

### 7.3

EstimatedRTT: 107.76 ms

DevRTT: 14.07 ms

TimeoutInterval: 164.02 ms

### 7.4

EstimatedRTT: 105.54 ms

DevRTT: 14.43 ms

TimeoutInterval: 163.28 ms

### 7.5

EstimatedRTT: 106.72 ms

DevRTT: 12.89 ms

TimeoutInterval: 158.30 ms

## 8

### a

1-6 and 23-26

### b

6-16 and 17-22

### c

Triple Duplicate ACK

### d

timeout

### e

32 segments

### f

21

### g

14

### h

7

### i

ssthresh = 21
cwnd = 4

### j

52

## 9

$$RTT_1 + RTT_2 + \dots + RTT_n + 2RTT_0$$

## 10
### a

Alice's key: $$ S = T^{S_A}_B \:\%\: P = (g^{S_B} \:\%\: p)^{S_A} \:\%\: p = g^{S_AS_B} \:\%\: p $$
Bob's key: $$ S' = T^{S_B}_A \:\%\: P = (g^{S_A} \:\%\: p)^{S_B} \:\%\: p = g^{S_BS_A} \:\%\: p $$

### b

Alice's key: $$ T_A = g^{S_A} \:\%\: p = 32 \:\%\:11 = 10 $$
Bob's key: $$ T_B = g^{S_B} \:\%\: p = 4096 \:\%\:11 = 4 $$

### c

using Alice's key:
$$ S = T^{S_A}_B \:\%\: p = 4^5 :\%\: 11 = 1 $$

## 11

### a

n: 33
z: 20

### b 

$$ 1 < e <z $$
$$ 1 < 3 <20 $$
gcd(e,z) = 1

### c 

7

### d 

17