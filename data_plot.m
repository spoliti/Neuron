filename = 'file.txt';
M = csvread(filename);
m_x = size(M,1);
m_y = size(M,2);

t_start = 1000;
t_end = 2000;

figure;
j = 1;
while(j<m_y)
    i = 1;
    while(i<m_x)
        axis([t_start t_end 0 m])
        if(M(i,j) ~= 0)    
            plot(M(i,j), i, 'k.')
            hold on
        end
        i = i+1;
    end
    j = j+1;
end
xlabel('time (0.1 ms)')
ylabel('neurons')

figure;
filename = 'file_total.txt';
N = csvread(filename);
n_x = size(N,2);
n_max = max(N);
x = linspace(t_start, t_end, n_x);
bar(x, N)
axis ([t_start t_end 0 n_max])
xlabel('time (0.1 ms)')
ylabel('number of spikes')