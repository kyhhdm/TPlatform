
(setq project-name "mapreduce2")
(setq project-root "~/myWorkspace/tplatform/")
(setq project-executable "mapred_master")
(setq project-info "mapreduce of tplatform")

(global-set-key [f7] 'project-compile)
(global-set-key [C-f7] 'project-rebuild)
(global-set-key [C-M-f7] 'project-set-debug-mode)
(global-set-key [f8] 'project-run)
(global-set-key [C-M-f8] 'project-kill-process)
(global-set-key [f9] 'project-run-debug)


(cd  (concat project-root project-name))
(find-file "./build/Makefile")
(find-file "./src/master/MasterMain.cpp")