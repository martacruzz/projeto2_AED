% simple matlab scrip to process data on a txt file and produce some graphs
% for vizualisation of growing complexity

% Base directory for saving plots
base_path = "plots"; 

if ~exist(base_path, 'dir')

    mkdir(base_path);

end

% definition of input arguments - modify here to test worst / best case
MINVERTICES = 10;
INCVERTICES = 5;
MAXVERTICES = 500;

%% for Bellman best case

path = fullfile(base_path, 'bellman');

if ~exist(path, 'dir')

    mkdir(path);

end

% execute and read data file
status = system(sprintf("./execute_GraphTester.sh %d %d %d %d", MINVERTICES, INCVERTICES, MAXVERTICES, 0));

file = fopen("data_GraphTester.txt", "r");
formatSpec = '%15.6f\t%15.6f\t%15d\t%15d\t%15d\t%15d';
data = textscan(file, formatSpec, 'HeaderLines',1);
fclose(file);

% process variables
time = double(data{1});
calltime = double(data{2});
pixmem = double(data{3});
numruns = double(data{4});
memspace = double(data{5});

% number of runs in function of m
f1_runs = figure(1);
plot(m_array(1:end-1), numruns, 'o-')
xlabel("m (number of rows)")
ylabel("number of runs")
title("Number of runs in function of number of rows")
legend("complexity")
grid on

% save to file
exportgraphics(f1_runs, fullfile(path, 'numruns_vs_m.pdf'));

% memspace in function of m
f1_mem = figure(2);
plot(m_array(1:end-1), memspace, 'o-');
xlabel("m (number of rows)")
ylabel("space in memory")
title("Space in memory in function of number of rows")
legend("complexity")
grid on

%save to file
exportgraphics(f1_mem, fullfile(path, 'memspace_vs_m.pdf'));
