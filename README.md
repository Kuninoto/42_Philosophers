# Philosophers (42Porto - 42Cursus) <img src="https://github.com/devicons/devicon/blob/master/icons/linux/linux-original.svg" title="Linux" alt="Linux Logo" width="50" height="60" align="right" />&nbsp; <img src="https://github.com/devicons/devicon/blob/master/icons/c/c-original.svg" title="C" alt="C Logo" width="55" height="55" align="right" />&nbsp;  

## Grade: 125/100

### Installing and running the project:

###  Subject: [Philosophers en_subject](./extras/en.subject_philosophers.pdf)

#### Makefile Available Targets:  

### Useful links:  
General thread understanding:  
https://www.youtube.com/watch?v=ldJ8WGZVXZk  
https://www.youtube.com/watch?v=uA8X5zNOGw8&list=PL9IEJIKnBJjFZxuqyJ9JqVYmuFZHr7CFM  
https://www.youtube.com/watch?v=d9s_d28yJq0&list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2  
https://www.geeksforgeeks.org/multithreading-c-2/  
https://www.youtube.com/watch?v=FY9livorrJI  
https://www.youtube.com/watch?v=xoXzp4B8aQk  

Threads vs. Processes:  
https://www.geeksforgeeks.org/difference-between-process-and-thread/  
https://www.youtube.com/watch?v=IKG1P4rgm54  

Mutex:  
https://www.youtube.com/watch?v=oq29KUy29iQ  
https://www.geeksforgeeks.org/mutex-lock-for-linux-thread-synchronization/  

Project Guide:  
https://github.com/TommyJD93/Philosophers  

General semaphore understanding:  
https://www.geeksforgeeks.org/semaphores-in-process-synchronization/  
https://www.geeksforgeeks.org/use-posix-semaphores-c/  
https://www.youtube.com/watch?v=YSn8_XdGH7c  
https://www.youtube.com/watch?v=XDIOC2EY5JE  
https://www.youtube.com/watch?v=ukM_zzrIeXs  

Mutex vs. Semaphores:  
https://www.geeksforgeeks.org/mutex-vs-semaphore/  
https://www.youtube.com/watch?v=8wcuLCvMmF8  

Mutex vs. Semaphores Rule of Thumb:
<table>
 <tr>
   <th>Mutex</th>
   <th>Semaphores</th>
 </tr>
 <tr>
   <td>Behaves like a lock</td>
   <td>Behaves like a limited inventory</td>
 </tr>
 <tr>
   <td>pthread_mutex_lock()</td>
   <td>sem_wait(), decrements the number of available things, if sem == 0, waits.</td>
 </tr>
 <tr>
  <td>pthread_mutex_unlock()</td>
  <td>sem_post(), increments back the number of available things</td>
 </tr>
</table>

Dining Philosophers problem using Semaphores:    
https://www.geeksforgeeks.org/dining-philosopher-problem-using-semaphores/?ref=lbp    

## Disclaimer
> At [42School](https://en.wikipedia.org/wiki/42_(school)), almost every project must be written in accordance to the [Norm](./extras/en_norm.pdf), the schools' coding standard. As a result, the implementation of certain parts may appear strange and for sure had room for improvement.

---
Made by Nuno Carvalho (Kuninoto) | nnuno-ca@student.42porto.com  
<div id="badge"> <a href="https://www.linkedin.com/in/nuno-carvalho-218822247"/> <img src="https://img.shields.io/badge/LinkedIn-blue?style=for-the-badge&logo=linkedin&logoColor=white" alt="LinkedIn Badge"/>&nbsp;
