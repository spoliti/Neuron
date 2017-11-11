file_variables = 'file_variables.txt';
V = csvread(file_variables);
n = V(1,1);
t_start = V(1,2);
t_end = V(1,3);

file = 'file.txt';
M = csvread(file);
if(M == 0)
    figure
    axis([t_start t_end 0 n])
    dim = [.2 .5 .3 .3];
    str = 'No spikes were produced for the given time-range';
    annotation('textbox', dim, 'String',str, 'FitBoxToText', 'on')
else
    m_x = size(M,1);
    m_y = size(M,2);
    figure
    j = 1;
    while(j <= m_y)
        i = 1;
        while(i <= m_x)
            axis([t_start t_end 0 n])
            if(M(i,j) ~= 0)    
                plot(M(i,j), i, 'k.')
                hold on
            else
                plot(M(i,j), i, 'w.')
                hold on
            end
            i = i+1;
        end
        j = j+1;
    end
    xlabel('time (0.1 ms)')
    ylabel('neurons')
end

figure
file_total = 'file_total.txt';
N = csvread(file_total);
n_x = size(N,2);
n_max = max(N);
x = linspace(t_start, t_end, n_x);
bar(x, N)
axis ([t_start t_end 0 n_max])
xlabel('time (0.1 ms)')
ylabel('number of spikes')