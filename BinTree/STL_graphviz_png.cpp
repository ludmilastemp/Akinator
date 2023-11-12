digraph STL
{
rankdir = TB
graph [ splines = ortho, splines = true ]
node  [ shape = record, style = filled, fillcolor = "#E0FFFF", color = "#A0FFFF" ]
edge  [ arrowhead = none ]

f1 [label = " 10 " ]
f1->f5
f1->f2

f5 [label = " 5 "  ]
f5->f80
f5->f90
f80 [label = " nil ", fillcolor = "#E0FFDF", color = "#E0FFDF" ]
f90 [label = " nil ", fillcolor = "#E0FFDF", color = "#E0FFDF" ]

f2 [label = " 17 " ]
f2->f4
f2->f3

f4 [label = " 15 " ]
f4->f6
f4->f7
f6 [label = " nil ", fillcolor = "#E0FFDF", color = "#E0FFDF" ]
f7 [label = " nil ", fillcolor = "#E0FFDF", color = "#E0FFDF" ]

f3 [label = " 20 " ]
f3->f8
f3->f9
f8 [label = " nil ", fillcolor = "#E0FFDF", color = "#E0FFDF" ]
f9 [label = " nil ", fillcolor = "#E0FFDF", color = "#E0FFDF" ]

}
