%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%
%% function [x,chistory] = powermethod(P,alpha,tol,mu)
%%
%% efficient power method to compute stationary vector
%% the operator is:  
%%    A = alpha * P' + (1-alpha)ve'    
%% (personalization vector v=e/n is hard coded)
%% implicitly applies ve' and zero row corrections
%% applies shifts in mu
%% convergence history is the 1-norm difference of successive iterates
%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

function [x,chistory] = powermethod(P,alpha,tol,mu)

tic;
n = size(P,1);
x = ones(n,1) / n;
nmu = length(mu);

iteration = 0;
while (1)
  iteration = iteration + 1;
  x0 = x;
  x = alpha * (x'*P)';
  x = x + (1-sum(x))/n;   
%  x = x + 0.15/n;

  if (iteration <= nmu)
    x = x - mu(iteration)*x0;
    x = x/sum(x);
  end
  fprintf(1,'%d -th iteration\n', iteration);
  fprintf(1,'%d %d %d %d %d %d\n', x(1), x(2), x(3), x(4), x(5), x(6));
  
  % tracking convergence is noticably time consuming
  % one norm suggested by golub, norm(,1) is inefficient
  change = sum(abs(x-x0));           
  chistory(iteration) = change;
  if (change < tol)
    break;
  end
end

fprintf(1,'power method took %d iterations to converge to a tolerance of %e\n',iteration,tol);
fprintf(1,'  elapsed time = %f\n',toc);

