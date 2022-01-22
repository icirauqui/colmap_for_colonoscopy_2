// Copyright (c) 2018, ETH Zurich and UNC Chapel Hill.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//
//     * Neither the name of ETH Zurich and UNC Chapel Hill nor the names of
//       its contributors may be used to endorse or promote products derived
//       from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//
// Author: Johannes L. Schoenberger (jsch-at-demuc-dot-de)

// IC03 new class for bundled reconstruction

#include "ui/bundle_adjustment_widget.h"

#include "controllers/bundle_adjustment.h"
#include "ui/main_window.h"

namespace colmap {

ReconstructionBundleWidget::ReconstructionBundleWidget(MainWindow* main_window,
                                               OptionManager* options)
    : OptionsWidget(main_window),
      main_window_(main_window),
      options_(options) {

  setWindowTitle("Reconstruction Bundles");

  AddOptionInt(&options_->mapper->frames_between_bundles,"Frames Between Bundles");
  AddOptionInt(&options_->mapper->bundle_size,"Bundle Size");
  AddOptionInt(&options_->mapper->min_3Ds_for_validation,"Min number of 3Ds");

  AddSpacer();

  QPushButton* run_button = new QPushButton(tr("Run"), this);
  grid_layout_->addWidget(run_button, grid_layout_->rowCount(), 1);
  connect(run_button, &QPushButton::released, this,
          &ReconstructionBundleWidget::Run);


  render_result_ = new QAction(this);
  connect(render_result_, &QAction::triggered, this,
          &ReconstructionBundleWidget::RenderResult, Qt::QueuedConnection);
}



void ReconstructionBundleWidget::Run() {
  if (!main_window_->mapper_controller_->IsStarted() && !main_window_->options_.Check()) {
    main_window_->ShowInvalidProjectError();
    return;
  }

  if (main_window_->mapper_controller_->IsFinished() && main_window_->HasSelectedReconstruction()) {
    QMessageBox::critical(this, "",
                          tr("Reset reconstruction before starting."));
    return;
  }

  if (main_window_->mapper_controller_->IsStarted()) {
    // Resume existing reconstruction.
    main_window_->timer_.Resume();
    main_window_->mapper_controller_->Resume();
  } else {
    // Start new reconstruction.
    main_window_->CreateControllers();
    main_window_->timer_.Restart();
    main_window_->mapper_controller_->Start();
    main_window_->action_reconstruction_start_->setText(tr("Resume reconstruction"));
  }

  main_window_->DisableBlockingActions();
  main_window_->action_reconstruction_pause_->setEnabled(true);
}


void ReconstructionBundleWidget::RenderResult() {
}




void ReconstructionBundleWidget::Render() { //main_window_->RenderNow(); 
}

}  // namespace colmap
