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

%% Bellman best case

path = fullfile(base_path, 'bellman');

if ~exist(path, 'dir')

    mkdir(path);

end

% execute and read data file
status = system(sprintf("./execute_GraphTester.sh %d %d %d %d", MINVERTICES, INCVERTICES, MAXVERTICES, 0));

file = fopen("data.txt", "r");
formatSpec = '%15.6f\t%15.6f\t%15d';
data = textscan(file, formatSpec, 'HeaderLines',2);
fclose(file);

% process variables
iters_bb = double(data{3});

% number of iterations in function of number of vertices
f1 = figure(1);
plot(MINVERTICES:INCVERTICES:MAXVERTICES, iters_bb, 'o-')
xlabel("number of vertices")
ylabel("number of iterations")
title("Bellman-Ford algorithm complexity analysis - best case")
legend("best case")
grid on

% save to file
exportgraphics(f1, fullfile(path, 'best_case.pdf'));

%% bellman worst case
status = system(sprintf("./execute_GraphTester.sh %d %d %d %d", MINVERTICES, INCVERTICES, MAXVERTICES, 1));

file = fopen("data.txt", "r");
formatSpec = '%15.6f\t%15.6f\t%15d';
data = textscan(file, formatSpec, 'HeaderLines',2);
fclose(file);

% process variables
iters_bw = double(data{3});

% PLOT

% number of iterations in function of number of vertices
f2 = figure(2);
plot(MINVERTICES:INCVERTICES:MAXVERTICES, iters_bw, 'o-')
xlabel("number of vertices")
ylabel("number of iterations")
title("Bellman-Ford algorithm complexity analysis - worst case")
legend("worst case")
grid on

% save to file
exportgraphics(f2, fullfile(path, 'worst_case.pdf'));

%% transitive best case

path = fullfile(base_path, 'transitive');

if ~exist(path, 'dir')

    mkdir(path);

end

status = system(sprintf("./execute_GraphTester.sh %d %d %d %d", MINVERTICES, INCVERTICES, MAXVERTICES, 2));

file = fopen("data.txt", "r");
formatSpec = '%15.6f\t%15.6f\t%15d';
data = textscan(file, formatSpec, 'HeaderLines',2);
fclose(file);

% process variables
iters_tb = double(data{3});

% PLOT

% number of iterations in function of number of vertices
f3 = figure(3);
plot(MINVERTICES:INCVERTICES:MAXVERTICES, iters_tb, 'o-')
xlabel("number of vertices")
ylabel("number of iterations")
title("Transitive Closure algorithm complexity analysis - best case")
legend("best case")
grid on

% save to file
exportgraphics(f3, fullfile(path, 'best_case.pdf'));

%% transitive worst case

status = system(sprintf("./execute_GraphTester.sh %d %d %d %d", MINVERTICES, INCVERTICES, MAXVERTICES, 3));

file = fopen("data.txt", "r");
formatSpec = '%15.6f\t%15.6f\t%15d';
data = textscan(file, formatSpec, 'HeaderLines',2);
fclose(file);

% process variables
iters_tw = double(data{3});

% PLOT

% number of iterations in function of number of vertices
f4 = figure(4);
plot(MINVERTICES:INCVERTICES:MAXVERTICES, iters_tw, 'o-')
xlabel("number of vertices")
ylabel("number of iterations")
title("Transitive Closure algorithm complexity analysis - worst case")
legend("worst case")
grid on

% save to file
exportgraphics(f4, fullfile(path, 'worst_case.pdf'));