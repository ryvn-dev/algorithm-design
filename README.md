# Algorithm Design

The current repository includes my homeworks and implementations in the course of **Algorithm Design** [NTUEE4033] lectured by HUI-RU JIANG in National Taiwan University. The projects materialized by me are Bezier Curve, Optimal Wiring Topology for Electromigration Avoidance, and Electric Transpotation Interection Manager.

## Bezier Curve

A Bézier curve is defined by a set of control points $p_0$ through $p_n$ , where $n$ is called its degree. I have written a program to generate the Bézier curve for a given set of points based on dynamic programming.

## Optimal Wiring Topology for Electromigration Avoidance

Given a set $S = \{s_1, s_2, …, s_m\}$ of m current sources, a set $T = \{t_1, t_2, …, t_n\}$ of n current sinks, each current source $i$ (sink $j$) is associated with its flow $f_{s_i}(f_{t_j})$ construct a wiring topology to connect all current sources and sinks in $S+T$, such that the total wire area is minimized and electromigration is avoided.

I adopted Bellman-Ford and Dijkstra approach to realize the implementation.

For more information, please see [1] and [2].

[1] Iris Hui Ru Jiang, Hua Yu Chang, and Chih Long Chang, “WiT: Optimal wiring topology for electromigration avoidance,” *IEEE Transactions on Very Large Scale Integration Systems (TVLSI)*, vol. no. 4, Apr. 2012, pp. 581 592. Also see in Proc. 19th ACM Inter national Symposium on Physical Design (ISPD 2010)2010), San Francisco, CA, Mar. 2010, pp. 177 184. Slides [Online](http://www.ispd.cc/slides/slides10/8_05.pdf)

[2] Jing Wei Lin, Tsung Yi Ho, and Iris Hui Ru Jiang, “Reliability driven power/ground routing for analog ICs,” *ACM Transactions on Design Automation of Electronic Systems (TODAES) TODAES)*, vol. 17, no. 1, Jan. 2012, pp. 6:1 6:26.

## Electric Transpotation Intersection Manager

I adopted a greedy approach by 3 heuristics due to pragmatic concerns.

## Others
(note that grade = A)

## MathJax

The current depository may include mathmetical expressions, please plug [MathJax](https://chrome.google.com/webstore/detail/mathjax-plugin-for-github/ioemnmodlmafdkllaclgeombjnmnbima) in your chrome.
