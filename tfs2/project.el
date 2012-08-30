(setq project-name "tfs")
(setq project-root "~/myWorkspace/tplatform/")
(setq project-executable "tfs_master")
(setq project-info "tianwang filesystem of tplatform")

(global-set-key [f7] 'project-compile)

(cd  (concat project-root project-name))
(find-file "./master/MasterMain.cpp")